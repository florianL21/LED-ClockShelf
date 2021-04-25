import React from "react";
import SettingsForm from '../components/SettingsForm'

const Settings = (props) => {
  return (
	<div className="mt-8 p-6 sm:mx-auto sm:w-full xl:max-w-6xl">
		<div className="bg-white py-8 px-6 shadow rounded-lg sm:py-10">
			<div>
				<h2 className="mt-6 text-center text-3xl font-extrabold text-gray-900">{props.children}</h2>
			</div>
			<SettingsForm domain={props.domain} onSubmit={props.onSubmit} UIDefinition={props.UIDefinition} InitialValues={props.InitialValues}/>
		</div>
	</div>
  );
}

export default Settings;
