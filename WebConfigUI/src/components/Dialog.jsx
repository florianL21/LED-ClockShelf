import { Dialog, Transition } from "@headlessui/react";
import React, { Fragment, useRef} from "react";

export default function MyModal(props) {
	let OkayButtonRef = useRef();

	props.type == "OK/Cancel"

	let cancelButton = ""
	let okayButtonLabel = "OK"

	if(props.confirmMessage)
	{
		okayButtonLabel = props.confirmMessage
	}

	if(props.type == "OK/Cancel")
	{
		cancelButton = (
			<button
				type="button"
				className="w-full inline-flex text-sm font-medium btn btn-secondary uppercase"
				onClick={() => props.onClose(false)}
			>
				Cancel
			</button>
		)
	}

	return (
		<Transition show={props.show} as={Fragment}>
			<Dialog
				as="div"
				id="modal"
				className="fixed inset-0 z-10 overflow-y-auto"
				static
				initialFocus={OkayButtonRef}
				open={props.show}
				onClose={() => props.onClose(false)}
			>
				<div className="min-h-screen px-4 text-center">
					<Transition.Child
						as={Fragment}
						enter="ease-out duration-300"
						enterFrom="opacity-0"
						enterTo="opacity-100"
						leave="ease-in duration-200"
						leaveFrom="opacity-100"
						leaveTo="opacity-0"
					>
						<Dialog.Overlay className="fixed inset-0 bg-gray-500 bg-opacity-75 transition-opacity"/>
					</Transition.Child>
					<Transition.Child
						as={Fragment}
						enter="ease-out duration-300"
						enterFrom="opacity-0 scale-95"
						enterTo="opacity-100 scale-100"
						leave="ease-in duration-200"
						leaveFrom="opacity-100 scale-100"
						leaveTo="opacity-0 scale-95"
					>
						<div className="inline-block w-full sm:max-w-lg p-6 my-8 overflow-hidden text-left align-middle transition-all transform bg-white shadow-xl rounded-2xl">
							<Dialog.Title
								as="h1"
								className="text-2xl font-medium text-gray-900"
							>
								{props.title}
							</Dialog.Title>
							<Dialog.Description as="div" className="mt-2">
								<p className="text-lg text-gray-500">
									{props.children}
								</p>
							</Dialog.Description>

							<div className="mt-4 space-y-4">
								<button type="button" ref={OkayButtonRef} onClick={() => props.onClose(true)} className="w-full inline-flex btn btn-primary float-right uppercase">
									{okayButtonLabel}
								</button>
								{cancelButton}
							</div>
						</div>
					</Transition.Child>
				</div>
			</Dialog>
		</Transition>
	);
}
