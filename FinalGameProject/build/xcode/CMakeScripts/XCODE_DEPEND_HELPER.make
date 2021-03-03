# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Gal.Debug:
/Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/Debug/Gal:\
	/usr/local/lib/libsfml-graphics.2.5.1.dylib\
	/usr/local/lib/libsfml-audio.2.5.1.dylib\
	/usr/local/lib/libsfml-window.2.5.1.dylib\
	/usr/local/lib/libsfml-system.2.5.1.dylib
	/bin/rm -f /Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/Debug/Gal


PostBuild.Gal.Release:
/Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/Release/Gal:\
	/usr/local/lib/libsfml-graphics.2.5.1.dylib\
	/usr/local/lib/libsfml-audio.2.5.1.dylib\
	/usr/local/lib/libsfml-window.2.5.1.dylib\
	/usr/local/lib/libsfml-system.2.5.1.dylib
	/bin/rm -f /Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/Release/Gal


PostBuild.Gal.MinSizeRel:
/Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/MinSizeRel/Gal:\
	/usr/local/lib/libsfml-graphics.2.5.1.dylib\
	/usr/local/lib/libsfml-audio.2.5.1.dylib\
	/usr/local/lib/libsfml-window.2.5.1.dylib\
	/usr/local/lib/libsfml-system.2.5.1.dylib
	/bin/rm -f /Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/MinSizeRel/Gal


PostBuild.Gal.RelWithDebInfo:
/Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/RelWithDebInfo/Gal:\
	/usr/local/lib/libsfml-graphics.2.5.1.dylib\
	/usr/local/lib/libsfml-audio.2.5.1.dylib\
	/usr/local/lib/libsfml-window.2.5.1.dylib\
	/usr/local/lib/libsfml-system.2.5.1.dylib
	/bin/rm -f /Users/bradenmcclean/FinalProjectGal/CS6010_FinalProject/build/xcode/RelWithDebInfo/Gal




# For each target create a dummy ruleso the target does not have to exist
/usr/local/lib/libsfml-audio.2.5.1.dylib:
/usr/local/lib/libsfml-graphics.2.5.1.dylib:
/usr/local/lib/libsfml-system.2.5.1.dylib:
/usr/local/lib/libsfml-window.2.5.1.dylib:
