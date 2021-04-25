import { Link, withRouter } from "react-router-dom";
import { Menu } from "@headlessui/react";
import React from "react";

const pages = [
  {link: "/WIFI", label: "WIFI Setup"},
  {link: "/BaseSettings", label: "Base Settings"},
  {link: "/Colors", label: "Colors"},
  {link: "/HWSetup", label: "Hardware Setup"},
  {link: "/", label: "Display Setup"},
  {link: "/", label: "Animation Setup"},
];

function NavigationMenu(props) {
  return (
    <div>
      <h1 className="text-6xl w-full text-center my-8">LED Pixel Clock</h1>
      <div className="my-8 sm:mx-auto sm:w-full sm:max-w-md">
        <Menu as="div" className="">
          <Menu.Items as="div" static className="mb-0 space-y-4">
            {pages.map((page) =>(
              <Menu.Item as="div" key={page.label} className="block items-center">
                {({ active }) => (
                  <Link to={page.link} className={`${
                    active ? "bg-indigo-500 text-white" : "text-gray-900"}
                    flex w-full text-2xl shadow bg-white py-8 px-6 sm:px-10 rounded-lg justify-center`}>
                      {page.label}
                  </Link>
                )}
              </Menu.Item>
            ))}
          </Menu.Items>
        </Menu>
      </div>
    </div>
  );
}

export default withRouter(NavigationMenu);
