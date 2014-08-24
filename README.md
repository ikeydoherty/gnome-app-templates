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


** NOTE **:
I am in the process of upstreaming this work. I hope that GatSidebar will
appear in GTK+ 3.15 under a yet-to-be-decided name. Further discussion needs
to happen with upstream first on "profiled" windows, i.e.  specific view types,
like the SidebarWindow

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
gnome-app-templates is available under the terms of the LGPL-2.1 license
(GNU Lesser General Public License Version 2.1)

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
