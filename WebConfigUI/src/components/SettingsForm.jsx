import React, { useEffect, useState } from "react";
import Dialog from '../components/Dialog'


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
				newSettingValue[target] = newValue;
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
						<div className="grid grid-cols-3">
							<div className="w-28 h-28 m-3 rounded-lg border-2" style={{backgroundColor: toColorStyle(rgbColor)}}></div>
							<div className="col-span-2 h-full space-y-6 m-4 pt-2">
								<div className="flex">
									<label className="inline px-2">{rgbColor.r}</label>
									<input disabled={Disabled} type='range' step="1" min='0' max='255' id="r" className="inline" name={settingEntry.target + "r"} value={rgbColor.r} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
								</div>
								<div className="flex">
									<label className="inline px-2">{rgbColor.g}</label>
									<input disabled={Disabled} type='range' step="1" min='0' max='255' id="g" className="inline" name={settingEntry.target + "g"} value={rgbColor.g} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
								</div>
								<div className="flex">
									<label className="inline px-2">{rgbColor.b}</label>
									<input disabled={Disabled} type='range' step="1" min='0' max='255' id="b" className="inline" name={settingEntry.target + "b"} value={rgbColor.b} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
								</div>
							</div>
						</div>
					</div>
				)
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
