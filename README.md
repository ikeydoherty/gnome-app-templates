What will eventually become a set of app "templates" to enable developers
to quickly and easily create native looking GNOME3 applications.

Why?
-----
Fair question. The aim of this library is to provide reusable application
templates, enabling people to quickly and easily develop cohesive looking
UIs across their various applications on the GNOME platform.

As the project continues, you may wish to keep track of the "sloccount"
of the `src/` directory. This will give a good indication of how much work
each developer is saved from each time :)

Stability
------
Not at a point where this is even being considered yet. Note however
that in future, proper deprecation of symbols will be introduced over time,
and compatibility will be retained over stretched out periods to ensure
painless transition for developers.

Bindings
------
Gat builds GObject Introspection bindings at build time, enabling you to
use any GI capable language with the library:

 * Vala (not yet ready)
 * JavaScript
 * Python

License
------
gnome-app-templates is available under the terms of the GPL-2.0 license
(GNU General Public License Version 2)

Disclaimer/legal
-----
"gnome-app-templates" is not officially affiliated with the GNOME project,
the GNOME foundation or any of its representatives. The GNOME name is a
trademark of the GNOME foundation.

Documentation
-----
API documentation can be found at: http://ikeydoherty.github.io/gnome-app-templates/

Note this is currently very much Work In Progress, so allow time for this
library to stabilize before its deemed usable

Author
------
 * Ikey Doherty <ikey.doherty@gmail.com>
