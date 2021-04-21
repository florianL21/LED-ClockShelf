import React, { useEffect, useState } from "react";
import Dialog from '../components/Dialog'
import settingsEntries from '../data/BaseConfig_definition'
import settingsValues from '../data/BaseConfig.json'

const loadConfig = () => {
  const settings = [...settingsEntries];
  settingsEntries.forEach((element, index) => {
    settings[index].value = settingsValues[element.target];
  });
  return settings;
}

const Settings = () => {
  const [Settings, setSettings] = useState(loadConfig());
	const [dialogShown, setDialogShown] = useState(false);

	const handleSubmit = (event) => {
		event.preventDefault();
		setDialogShown(true);
	}

	const handleDialogClose = (result) => {
		setDialogShown(false);
		if(result == true)
		{

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
        if(isNaN(newValue) || newValue < setting.min || newValue > setting.max)
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
      const targetSettingIndex = Settings.findIndex(p => p.target === setting.onlyIf);
      if(Settings[targetSettingIndex].type === "bool")
      {
        return !Settings[targetSettingIndex].value;
      }
    }
    return false;
  }

  const settingsForm = Settings.map((settingEntry, index) => {
    let Disabled = isDisabled(settingEntry);
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
      case "int":
        return (
          <div key={settingEntry.target}>
            <label htmlFor={settingEntry.target} className={`block text-sm font-medium ${Disabled ? "text-gray-400" : "text-gray-800"}`}>{settingEntry.label}</label>
            <div className="mt-1">
              <input disabled={Disabled} min={settingEntry.min} max={settingEntry.max} className={Disabled ? "border-gray-200 text-gray-400" : ""} id={settingEntry.target} name={settingEntry.target} value={Settings[index].value} onChange={(e) => valueChangedHandler(e, settingEntry.target)} autoComplete="off" type="number"/>
            </div>
          </div>
        )
    }
  })
  return (
    <div className="mt-8 p-6 sm:mx-auto sm:w-full md:max-w-2xl lg:max-w-4xl xl:max-w-6xl">
      <div className="bg-white py-8 px-6 shadow rounded-lg sm:py-10">
        <div>
          <h2 className="mt-6 text-center text-3xl font-extrabold text-gray-900">General Settings</h2>
        </div>
        <form className="mt-10 mb-0 space-y-6" onSubmit={handleSubmit}>
          {settingsForm}
          <div>
            <button type="submit" className="flex w-full btn btn-primary">
              Save
            </button>
          </div>
        </form>
      </div>
      <Dialog show={dialogShown} onClose={handleDialogClose} confirmMessage="Continue" title="Warning" type="OK/Cancel">
        To save the changes The device will reboot. You may loose connection to this interface temporarily.
      </Dialog>
    </div>
  );
}

export default Settings;