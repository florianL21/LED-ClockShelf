import React from "react";
import { BrowserRouter as Router, Route, Switch } from "react-router-dom";

import Navigation from "./sites/Navigation";
import WIFI_setup from "./sites/WIFI-setup";
import Settings from "./sites/Settings";

export default function App() {
  return (
    <div>
        <Router>
            <Switch>
                <Route path="/" exact component={() => <Navigation/> } />
                <Route path="/WIFI" exact component={() => <WIFI_setup />} />
                <Route path="/Settings" exact component={() => <Settings />} />
            </Switch>
        </Router>
    </div>
  );
}
