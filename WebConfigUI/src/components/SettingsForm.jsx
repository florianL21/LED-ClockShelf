import React, { useState } from "react";
import Dialog from '../components/Dialog'


const loadConfig = (UIDefinition, InitialValues) => {
	const settings = [...UIDefinition];
	UIDefinition.forEach((element, index) => {
	settings[index].value = InitialValues[element.target];
	});
	return settings;
}

const SettingsForm = (props) => {
	const [Settings, setSettings] = useState(loadConfig(props.UIDefinition, props.InitialValues));
	const [dialogShown, setDialogShown] = useState(false);

	const handleSubmit = (event) => {
		event.preventDefault();
		setDialogShown(true);
	}

	const handleDialogClose = (result) => {
		setDialogShown(false);
		if(result == true)
		{
			let results = {};
			Settings.forEach(setting => {
				results[setting.target] = setting.value
			});
			props.onSubmit(props.domain, JSON.stringify(results));
		}
	}

	const valueChangedHandler = (event, target) => {
		const targetSettingIndex = Settings.findIndex(p => p.target === target);

		const setting = {
		...Settings[targetSettingIndex]
		};

		const newValue = event.target.value;
		switch(event.target.type)
		{
			case "checkbox":
				setting.value = event.target.checked;
				break;
			case "number":
				if(isNaN(newValue) || (newValue < setting.min || newValue > setting.max) && newValue != "" || newValue.includes("e") || (newValue.includes(".") && setting.type === "int"))
				{
					return;
				}
			default:
				setting.value = newValue;
				break;
		}

		const settings = [...Settings];
		settings[targetSettingIndex] = setting;
		setSettings(settings);
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
					return Settings[targetSettingIndex].value;
				}
				else
				{
					return !Settings[targetSettingIndex].value;
				}
			}
		}
		return false;
	}

	const toColor = (num) => {
			num >>>= 0;
			var b = num & 0xFF,
					g = (num & 0xFF00) >>> 8,
					r = (num & 0xFF0000) >>> 16;
			return "rgba(" + [r, g, b, 1].join(",") + ")";
	}

	const settingsForm = Settings.map((settingEntry, index) => {
		let Disabled = isDisabled(settingEntry);
		let stepSize = 1;
		switch(settingEntry.type)
		{
			case "string":
				return (
					<div key={settingEntry.target}>
						<label htmlFor={settingEntry.target} className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
						<div className="mt-1">
							<input disabled={Disabled} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)} autoComplete="off" type="text"/>
						</div>
					</div>
				)
			case "bool":
				return (
					<div className="flex items-center" key={settingEntry.target}>
						<input disabled={Disabled} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} type="checkbox" checked={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)}/>
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
							<input disabled={Disabled} step={stepSize} min={settingEntry.min} max={settingEntry.max} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)} autoComplete="off" type="number"/>
						</div>
					</div>
				)
			case "color":
				const test = {
					backgroundColor: toColor(Settings[index].value)
				}
				return (
					<div key={settingEntry.target}>
						<label htmlFor={settingEntry.target} className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
						<div className="w-3.5 h-3.5" style={test}></div>
						<div className="mt-1">
							<input type="range" step="1" min="0" max="1" className="absolute pointer-events-none appearance-none z-20 h-2 w-full opacity-0 cursor-pointer"/>
							<input disabled={Disabled} min="0" max="255" step="1" className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)} type="range"/>
							<input disabled={Disabled} min="0" max="255" step="1" className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)} type="range"/>
							<input disabled={Disabled} min="0" max="255" step="1" className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)} type="range"/>
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
