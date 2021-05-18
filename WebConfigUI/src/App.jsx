import React, { useEffect, useState } from "react";
import { BrowserRouter as Router, Route, Switch } from "react-router-dom";

import Navigation from "./sites/Navigation";
import WIFI_setup from "./sites/WIFI-setup";
import Settings from "./sites/Settings";
import Dialog from './components/Dialog';

export default function App() {
	const [saveResponse, setSaveResponse] 		= useState("ERROR: Not saved");
	const [dialogShown, setDialogShown] 			= useState(false);

	// Function for fetching the config file from the server
	const getConfigFile = async (fileUrl, hook) => {
		const requestOptions = {
			method: 'GET',
			headers: { 'Content-Type': 'application/json' }
		};
		const response = await fetch(fileUrl, requestOptions);
		if (!response.ok) {
				console.log("Error while getting config file: " + response.statusText);
				return;
		}
		const parsedJson = await response.json();
		hook(parsedJson);
	}

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
				console.log("Error while putting config file: " + response.statusText);
				return false;
		}
		setSaveResponse(await response.text());
		setDialogShown(true);
		return true;
	}


	const handleSubmit = (domain, values, setter) => {
		putConfigFile(domain, values);
		if(setter != null)
		{
			getConfigFile(domain + '.json', setter);
		}
	}

	return (
		<div>
				<Router>
					<Switch>
						<Route path="/" exact component={() => <Navigation/> } />
						<Route path="/WIFI" exact component={() =>
							<WIFI_setup domain="WIFISettings" onSubmit={(d, v)=> handleSubmit(d, v, null)}/>} />
						<Route path="/BaseSettings" exact component={() =>
							<Settings domain="BaseConfig" onSubmit={handleSubmit} getUI={(setter)=>getConfigFile('UI_definitions.json', setter)} getValues={(setter)=>getConfigFile('BaseConfig.json', setter)}>
								General Settings
							</Settings>} />
						<Route path="/Colors" exact component={() =>
							<Settings domain="ColorConfig" onSubmit={handleSubmit} getUI={(setter)=>getConfigFile('UI_definitions.json', setter)}  getValues={(setter)=>getConfigFile('ColorConfig.json', setter)}>
								Color Settings
							</Settings>} />
						<Route path="/HWSetup" exact component={() =>
							<Settings domain="HWConfig" onSubmit={handleSubmit} getUI={(setter)=>getConfigFile('UI_definitions.json', setter)} getValues={(setter)=>getConfigFile('HWConfig.json', setter)}>
								Hardware Settings
							</Settings>} />
					</Switch>
				</Router>
				<Dialog show={dialogShown} onClose={(result)=>setDialogShown(false)} confirmMessage="OK" title="Info" type="OK">
					{saveResponse}
				</Dialog>
		</div>
	);
}
