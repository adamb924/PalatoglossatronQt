PalatoglossatronQt
------------

PalatoglossatronQt is for analyzing ultrasound images of the tongue, providing an implementation of the Palatron algorithm (Mielke et al. 2005) and of the Glossatron algorithm for automatic tracing. That's either enough information or it isn't. :-)

*   Setting up a project:
    *   Key terms: Each project file is an _Experiment_. You experiment can have many _Subjects_. Your subjects can have many _Sessions_. (Palatron adjustment is specific to the session.) Each session has many _Images_.
    *   When you create a project it's important to include all of the trace and measurement points that you'll ever want. (You don't have to use them all.)
*   Tips for getting started:
    *   As of February 2014, it's been three or four years since I've looked at this, so my memory is fuzzy about how it works.
    *   I don't like buttons: try clicking or double-clicking. Pay attention to the status bar for instructions.
    *   First thing, define an appropriate radial grid for yourself. “Annotations” | “Grid” tab | “Define radial grid”. Then follow the instructions on the task bar. Change “Number of intermediate lines” to something higher. (For doing stats later, the more points you have, the easier it will be to get statistical significance.) Redo it if necessary.
    *   In tracing images: left-click and drag to create points; right-click and drag to remove points. Shift-and-click to remove all the points to the left or right of where you click.
    *   Keyboard shortcuts: A for auto-trace. X to clear the trace entirely. Left or right arrows to move to the next or previous image in the session.
    *   Auto-tracing with glossatron: the initial settings are terrible. It helps if Glossatron knows where to look for the tongue, for which it needs an upper and lower bound. Once you have a grid, trace the lower bound across the entire grid: Glossatron won't look lower than this. Then go to the “Plugin Settings” menu | “Glossatron” | “Trace settings” | “Lower bound”. Then do the same for the upper bound.
    *   FWIW, I created the Glossatron algorithm, but in spite of the strong attraction of tracing being done automatically, what I found most helpful was to have an interface that made it quick to edit the results of automatic tracing.
    *   Try stuff. I knew the workflow very well when I wrote this, so I probably did stuff that makes sense to me.
    *   Saving and exporting your data. When you save your project file, it will put everything in XML format. That's a very nice format if you know XML technology. The best way to do this is with XSL stylesheets. There is one XSL stylesheet for exporting data in a format that is useful for [SSANOVA](/ssanova) analysis. To use this, you would do “File” | “Export data...” and then select “ssanova.xsl” and then enter a filename for the export. Processing the project file with XSL is not easy, but you can do anything you want to the file ([no, really!](http://conferences.idealliance.org/extreme/html/2004/Kepser01/EML2004Kepser01.html)), so it is also very powerful.
*   Caveats
    *   It makes sense to me, but you may not be me...
    *   (For programmers) The code is quite a mess: no comments to speak of, and the methods aren't even sorted. This is more or less the first complex program I attempted in the Qt framework. It is bound to be full of code that I would now find embarrassing.

Downloads
---------

PalatoglossatronQt is created with the [Qt application framework](https://www.qt.io/), released under the GNU Public License. That means, among other things, that you are free to download it and use it, but not to re-sell it.

Qt is a cross-platform framework, so there is the possibility for using this on Mac OS X, Linux, etc. Right now I only have Windows executables because I only have a Windows machine. Perhaps some do-gooder will build versions for other operating systems and send them to me.

I build in Windows with this, which assumes that Qt is installed and visible in your path:

```
qmake -config release
mingw32-make
```

Of course your system would have something different from “mingw32-make”—probably just “make”—if you are not building from Windows using MinGW.
