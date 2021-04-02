# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
import subprocess
sys.path.insert(0, os.path.abspath('..'))
# sys.path.insert(0, os.path.abspath('../lib/LED_clock/Config/Setup'))


# subprocess.call('doxygen', shell=True)



# -- Project information -----------------------------------------------------

project = 'LED-Clock'
copyright = '2021, Florian Laschober'
author = 'Florian Laschober'

# The full version, including alpha/beta/rc tags
release = '2.0.0'

primary_domain = 'cpp'
highlight_language = 'cpp'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ["breathe", "m2r2", 'exhale']

breathe_projects = { "LED-Clock": "./doxygen/xml" }

breathe_default_project = "LED-Clock"

import textwrap
# Setup the exhale extension
exhale_args = {
    "containmentFolder":     "./doxyapi",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "Library API",
    "doxygenStripFromPath":  "..",
    "createTreeView":        True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin":    textwrap.dedent('''
        INPUT      = ../lib
        PREDEFINED             += "IRAM_ATTR="
        EXCLUDE                = ../lib/LED_clock/Config/Animations/clock-only \
                         ../lib/LED_clock/Config/Animations/diy-machines \
                         ../lib/LED_clock/Config/Setup/diy-machines \
                         ../lib/LED_clock/Config/Setup/clock-only
    ''')
}

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', 'doxygen']

source_suffix = ['.rst', '.md']

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'
