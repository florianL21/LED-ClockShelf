import React, { Fragment, useEffect, useState } from "react";
import Dialog from '../components/Dialog'
import { Listbox, Transition } from '@headlessui/react'
import { CheckIcon, SelectorIcon } from '@heroicons/react/solid'


const loadConfig = (UIDefinition, InitialValues) => {
	const settings = [...UIDefinition];
	UIDefinition.forEach((element, index) => {
	settings[index].value = InitialValues[element.target];
	});
	return settings;
}

const SettingsForm = (props) => {
	const [Settings, setSettings] = useState([]);
	const [Values, setValues] = useState([]);
	const [dialogShown, setDialogShown] = useState(false);

	useEffect(() => {
		props.getUI((value)=>{
			setSettings(value[props.domain]);
		});
		props.getValues(setValues);
	}, []);

	const handleSubmit = (event) => {
		event.preventDefault();
		setDialogShown(true);
	}

	const handleDialogClose = (result) => {
		setDialogShown(false);
		if(result == true)
		{
			let results = {};
			Settings.forEach((setting, i) => {
				if(Settings[i].type == "color")
				{
					results[setting.target] = toColorValue(Values[setting.target]);
				}
				else
				{
					results[setting.target] = Values[setting.target];
				}
			});
			props.onSubmit(props.domain, JSON.stringify(results));
		}
	}

	const valueChangedHandler = (event, target) => {
		const newSettingValue = {...Values};
		const targetSettingIndex = Settings.findIndex(p => p.target === target);
		const setting = Settings[targetSettingIndex];

		const newValue = event.target.value;
		switch(setting.type)
		{
			case "bool":
				newSettingValue[target] = event.target.checked;
				break;
			case "float":
			case "int":
				if(isNaN(newValue) || (newValue < setting.min || newValue > setting.max) && newValue != "" || newValue.includes("e") || (newValue.includes(".") && setting.type === "int"))
				{
					console.log("Invalid value");
					return;
				}
				newSettingValue[target] = parseInt(newValue, 10);
			case "color":
				parseRGBColor(target);
				switch (event.target.id) {
					case "r":
						newSettingValue[target].r = event.target.value;
						break;
					case "g":
						newSettingValue[target].g = event.target.value;
						break;
					case "b":
						newSettingValue[target].b = event.target.value;
						break;
					default:
						break;
				}
				break;
			default:
				newSettingValue[target] = newValue;
				break;
		}
		setValues(newSettingValue);
	}

	const isDisabled = (setting) => {
		if("onlyIf" in setting)
		{
			const invert = setting.onlyIf.startsWith("!");
			const onlyIfTarget = setting.onlyIf.replace("!", "");

			const targetSettingIndex = Settings.findIndex(p => p.target === onlyIfTarget);
			if(Settings[targetSettingIndex].type === "bool")
			{
				if(invert)
				{
					return Values[onlyIfTarget];
				}
				else
				{
					return !Values[onlyIfTarget];
				}
			}
		}
		return false;
	}

	const parseRGBColor = (target) => {
		if(typeof(Values[target]) !== 'object' && Values[target] !== null)
		{
			const newSettingValue = {...Values};
			newSettingValue[target] = toColor(Values[target]);
			setValues(newSettingValue);
			return newSettingValue[target];
		}
		return Values[target];
	}

	const toColor = (num) => {
			const rgbColor = {
				b: num & 0xFF,
				g: (num & 0xFF00) >> 8,
				r: (num & 0xFF0000) >> 16
			}
			return rgbColor;
	}

	const toColorStyle = (rgbColor) => {
		return "rgba(" + [rgbColor.r, rgbColor.g, rgbColor.b, 1].join(",") + ")";
	}

	const toColorValue = (rgbColor) => {
		return (rgbColor.r << 16) + (rgbColor.g << 8) + rgbColor.b;
	}

	const settingsForm = Settings.map((settingEntry, index) => {
		const Disabled = isDisabled(settingEntry);
		let stepSize = 1;
		switch(settingEntry.type)
		{
			case "string":
				return (
					<div key={settingEntry.target}>
						<label htmlFor={settingEntry.target} className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
						<div className="mt-1">
							<input disabled={Disabled} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Values[settingEntry.target] || ''} onChange={(e) => valueChangedHandler(e, settingEntry.target)} autoComplete="off" type="text"/>
						</div>
					</div>
				)
			case "bool":
				return (
					<div className="flex items-center" key={settingEntry.target}>
						<input disabled={Disabled} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} type="checkbox" checked={Values[settingEntry.target] || false} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
						<label htmlFor={settingEntry.target} className={`ml-2 block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
					</div>
				)
			case "float":
				stepSize = 0.1
			case "int":
				return (
					<div key={settingEntry.target}>
						<label htmlFor={settingEntry.target} className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
						<div className="mt-1">
							<input disabled={Disabled} step={stepSize} min={settingEntry.min} max={settingEntry.max} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Values[settingEntry.target] || ''} onChange={(e) => valueChangedHandler(e, settingEntry.target)} autoComplete="off" type="number"/>
						</div>
					</div>
				)
			case "color":
				let rgbColor = parseRGBColor(settingEntry.target);
				return (
					<div key={settingEntry.target}>
						<label className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
						<div className="flex flex-col sm:flex-row">
							<div className="sm:flex-none flex-grow sm:w-28 h-28 m-3 rounded-lg border-2" style={{backgroundColor: toColorStyle(rgbColor)}}></div>
							<div className="flex-grow h-full space-y-4 m-4 pt-2">
								<div className="flex">
									<label className="flex-none inline px-2 w-10 h-3">{rgbColor.r}</label>
									<input disabled={Disabled} type='range' step="1" min='0' max='255' id="r" className="flex-grow inline" name={settingEntry.target + "r"} value={rgbColor.r} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
								</div>
								<div className="flex">
									<label className="flex-none inline px-2 w-10 h-3">{rgbColor.g}</label>
									<input disabled={Disabled} type='range' step="1" min='0' max='255' id="g" className="flex-grow inline" name={settingEntry.target + "g"} value={rgbColor.g} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
								</div>
								<div className="flex">
									<label className="flex-none inline px-2 w-10 h-3">{rgbColor.b}</label>
									<input disabled={Disabled} type='range' step="1" min='0' max='255' id="b" className="flex-grow inline" name={settingEntry.target + "b"} value={rgbColor.b} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
								</div>
							</div>
						</div>
					</div>
				)
			case "dropdown":
				var selectedItem = Values[settingEntry.target] || '';
				var listboxOptions;
				if(Array.isArray(settingEntry.list))
				{
					listboxOptions = settingEntry.list.map((entry) => (
						<Listbox.Option
							key={entry.value}
							className={({ active }) => `${active ? 'text-amber-900 bg-amber-100' : 'text-gray-900'} cursor-default select-none relative py-2 pl-10 pr-4`}
							value={entry.value}
						>
							{({ selected, active }) => (
								<>
									<span className={`${ selected ? 'font-medium' : 'font-normal' } block truncate`}>
										{entry.label}
									</span>
									{selected ? (
										<span className={`${ active ? 'text-amber-600' : 'text-amber-600' } absolute inset-y-0 left-0 flex items-center pl-3`}>
											<CheckIcon className="w-5 h-5" aria-hidden="true" />
										</span>
									) : null}
								</>
							)}
						</Listbox.Option>
					))
				}
				return (
					<div key={settingEntry.target}>
						<label htmlFor={settingEntry.target} className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
						<div className="mt-1">
							<Listbox value={selectedItem} onChange={(e) => valueChangedHandler(e, settingEntry.target)}>
								<div className="relative mt-1">
									<Listbox.Button className="relative w-full py-2 pl-3 pr-10 text-left bg-white rounded-lg shadow-md cursor-default focus:outline-none focus-visible:ring-2 focus-visible:ring-opacity-75 focus-visible:ring-white focus-visible:ring-offset-orange-300 focus-visible:ring-offset-2 focus-visible:border-indigo-500 sm:text-sm">
										<span className="block truncate">{selectedItem}</span>
										<span className="absolute inset-y-0 right-0 flex items-center pr-2 pointer-events-none">
											<SelectorIcon
												className="w-5 h-5 text-gray-400"
												aria-hidden="true"
											/>
										</span>
									</Listbox.Button>
									<Listbox.Options className="absolute w-full py-1 mt-1 overflow-auto text-base bg-white rounded-md shadow-lg max-h-60 ring-1 ring-black ring-opacity-5 focus:outline-none sm:text-sm">
										{listboxOptions}
									</Listbox.Options>
								</div>
							</Listbox>
						</div>
					</div>
				);
			default:
				console.log(settingEntry.target + ": has invalid type: " + settingEntry.type);
				return (<div key={settingEntry.target} className="invalid"></div>);
		}
	})
	return (
	<div>
		<form className="mt-10 mb-0 space-y-6" onSubmit={handleSubmit}>
			{settingsForm}
			<div>
				<button type="submit" className="flex w-full btn btn-primary">
					Save
				</button>
			</div>
		</form>

		<Dialog show={dialogShown} onClose={handleDialogClose} confirmMessage="Continue" title="Warning" type="OK/Cancel">
			To save the changes the device may reboot. You may loose connection to this interface temporarily.
		</Dialog>
	</div>
	);
}

export default SettingsForm;
