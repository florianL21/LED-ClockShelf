import React, { useEffect, useState } from "react";
import { BrowserRouter as Router, Route, Switch } from "react-router-dom";

import Navigation from "./sites/Navigation";
import WIFI_setup from "./sites/WIFI-setup";
import Settings from "./sites/Settings";

import {BaseSettings, ColorSettings, HWSettings} from './data/UI_definitions'


// Development function for testing locally
const getConfigFile = async (fileUrl, hook) => {
	import(/* @vite-ignore */"./data" + fileUrl ).then(config => {
		hook(config);
	})
}

export default function App() {
	const [BaseConfig, setBaseConfig] = useState({});
	const [ColorConfig, setColorConfig] = useState({});
	const [HWConfig, setHWConfig] = useState({});

	// Function for fetching the config file from the server
	// const getConfigFile = async (fileUrl, hook) => {
	// 	const requestOptions = {
	// 		method: 'GET',
	// 		headers: { 'Content-Type': 'application/json' }
	// 	};
	// 	const response = await fetch(fileUrl, requestOptions);
	// 	if (!response.ok) {
	// 			console.log("Error while fetching config file: " + response.status);
	// 			return;
	// 	}
	// 	hook(response.json());
	// }

	const putConfigFile = async (fileUrl, value) => {
		console.log("Putting: " + value)
		console.log("To: " + fileUrl)
		const requestOptions = {
			method: 'PUT',
			headers: { 'Content-Type': 'application/json' },
			body: value
		};
		const response = await fetch(fileUrl, requestOptions);
		if (!response.ok) {
				console.log("Error while fetching config file: " + response.status);
				return null;
		}
		return await response.json();
	}

	useEffect(() => {
		getConfigFile('/BaseConfig.json', setBaseConfig);
		getConfigFile('/ColorConfig.json', setColorConfig);
		getConfigFile('/HWConfig.json', setHWConfig);
	}, []);

	const handleSubmit = (domain, values) => {
		putConfigFile(domain, values);
	}

	return (
		<div>
				<Router>
					<Switch>
						<Route path="/" exact component={() => <Navigation/> } />
						<Route path="/WIFI" exact component={() =>
							<WIFI_setup domain="WIFISettings" onSubmit={handleSubmit}/>} />
						<Route path="/BaseSettings" exact component={() =>
							<Settings domain="BaseConfig" onSubmit={handleSubmit} UIDefinition={BaseSettings} InitialValues={BaseConfig}>
								General Settings
							</Settings>} />
						<Route path="/Colors" exact component={() =>
							<Settings domain="ColorConfig" onSubmit={handleSubmit} UIDefinition={ColorSettings} InitialValues={ColorConfig}>
								Color Settings
							</Settings>} />
						<Route path="/HWSetup" exact component={() =>
							<Settings domain="HWConfig" onSubmit={handleSubmit} UIDefinition={HWSettings} InitialValues={HWConfig}>
								Hardware Settings
							</Settings>} />
					</Switch>
				</Router>
		</div>
	);
}
