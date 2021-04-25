import React, { useState } from 'react';
import Dialog from '../components/Dialog'

const WIFI_new = (props) => {
	const [SSID, setSSID] = useState("");
	const [PW, setPW] = useState("");
	const [createAP, setCreateAP] = useState(false);
	const [dialogShown, setDialogShown] = useState(false);

	const handleSSIDChanged = (object) => {
		setSSID(object.target.value);
	}

	const handlePWChanged = (object) => {
		setPW(object.target.value);
	}

	const handleCreateAPChanged = (object) => {
		setCreateAP(object.target.checked);
	}

	const handleSubmit = (event) => {
		event.preventDefault();
		setDialogShown(true);
	}

	const handleDialogClose = (result) => {
		setDialogShown(false);
		if(result == true)
		{
            setSSID("");
			setPW("");
			setCreateAP(false);
			props.onSubmit(props.domain, JSON.stringify({SSID: SSID, PW: PW, CreateAP: createAP}));
		}
	}

	return (
		<div className="mt-8 p-6 sm:mx-auto sm:w-full sm:max-w-md">
			<div className="bg-white py-8 px-6 shadow rounded-lg sm:py-10">
				<div>
					<h2 className="mt-6 text-center text-3xl font-extrabold text-gray-900">Connect to your WIFI</h2>
				</div>
				<form className="mt-10 mb-0 space-y-6" onSubmit={handleSubmit}>
					<div>
						<label htmlFor="SSID" className="block text-sm font-medium text-gray-700">SSID</label>
						<div className="mt-1">
							<input id="SSID" name="SSID" value={SSID} onChange={handleSSIDChanged} autoComplete="off" type="text" required/>
						</div>
					</div>
					<div>
						<label htmlFor="password" className="block text-sm font-medium text-gray-700">Password</label>
						<div className="mt-1">
							<input id="password" name="password" type="password" value={PW} onChange={handlePWChanged} autoComplete="current-password" required/>
						</div>
					</div>
					<div className="flex items-center">
						<input id="create-ap-instead" name="create-ap-instead" className="" type="checkbox" checked={createAP} onChange={handleCreateAPChanged}/>
						<label htmlFor="create-ap-instead" className="ml-2 block text-sm text-gray-900">
							Create an Access Point instead of connecting to an already existing WIFI network
						</label>
					</div>
					<div>
						<button type="submit" className="flex w-full btn btn-primary">
							Save and Connect
						</button>
					</div>
				</form>
			</div>
			<Dialog show={dialogShown} onClose={handleDialogClose} confirmMessage="Continue" title="Warning" type="OK/Cancel">To change WIFI settings the device has to restart. Please reconnect to the new device IP once it restarted.</Dialog>
		</div>
	)
}

export default WIFI_new;
