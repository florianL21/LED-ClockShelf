import React, { useState } from 'react';

const WIFI_new = () => {
	const [SSID, setSSID] = useState("");

	const handleSSIDChanged = (object) => {
		setSSID(object.target.value);
	}

	const handleSubmit = (event) => {
		event.preventDefault();
		console.log("SSID: " + SSID);
	}

	return (
		<div className="mt-8 sm:mx-auto sm:w-full sm:max-w-md">
			<div className="bg-white py-8 px-6 shadow rounded-lg sm:py-10">
				<div>
					<h2 className="mt-6 text-center text-3xl font-extrabold text-gray-900">Connect to your WIFI</h2>
				</div>
				<form className="mt-10 mb-0 space-y-6" onSubmit={handleSubmit}>
					<div>
						<label htmlFor="SSID" className="block text-sm font-medium text-gray-700">SSID</label>
						<div className="mt-1">
							<input id="SSID" name="SSID" value={SSID} onChange={handleSSIDChanged} type="text" required/>
						</div>
					</div>
					<div>
						<label htmlFor="password" className="block text-sm font-medium text-gray-700">Password</label>
						<div className="mt-1">
							<input id="password" name="password" type="password" autoComplete="current-password" required/>
						</div>
					</div>
					<div className="flex items-center">
						<input id="create-ap-instead" name="create-ap-instead" className="" type="checkbox"/>
						<label htmlFor="create-ap-instead" className="ml-2 block text-sm text-gray-900">
							Create an Access Point instead of connecting to an already existing WIFI network
						</label>
					</div>
					<div>
						<button type="submit" className="w-full flex justify-center py-2 px-4 border border-transparent
																						rounded-md shadow-sm text-sm font-medium text-white bg-indigo-600
																						hover:bg-indigo-700 focus:outline-none focus:ring-2 focus:ring-offset-2
																						focus:ring-indigo-500">
							Save and Connect
						</button>
					</div>
				</form>
			</div>
		</div>
	)
}

export default WIFI_new;