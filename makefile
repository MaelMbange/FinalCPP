.SILENT:

O = ./object
L = ./lib



ApplicHoraire:	main.o applichorairewindow.o moc_applichorairewindow.o $O/Event.o $O/Cours.o $O/Horaire.o $O/Professeur.o $O/Groupe.o $O/Local.o $O/Liste.o $O/Timing.o $O/Temps.o $O/Exception.o $O/TempsException.o $O/TimingException.o $O/planifiable.o $O/ListeTriee.o $O/Iterateur.o
		echo Creation de ApplicHoraire
		g++ -Wl,-O1 -o ApplicHoraire main.o applichorairewindow.o moc_applichorairewindow.o  /usr/lib64/libQt5Widgets.so /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so /usr/lib64/libGL.so -lpthread $O/Event.o $O/Cours.o $O/Horaire.o $O/Professeur.o $O/Groupe.o $O/Local.o $O/Liste.o $O/Timing.o $O/Temps.o $O/Exception.o $O/TempsException.o $O/TimingException.o $O/planifiable.o $O/ListeTriee.o $O/Iterateur.o -I $L					

main.o:	main.cpp
		echo Creation de main.o
		g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o main.o main.cpp

applichorairewindow.o:	applichorairewindow.cpp applichorairewindow.h ui_applichorairewindow.h
		echo Creation de applichorairewindow.o
		g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o applichorairewindow.o applichorairewindow.cpp

moc_applichorairewindow.o:	moc_applichorairewindow.cpp applichorairewindow.h
		echo Creation de moc_applichorairewindow.o
		g++ -c -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -I/usr/lib64/qt5/mkspecs/linux-g++ -o moc_applichorairewindow.o moc_applichorairewindow.cpp

$O/Event.o:	$L/Event.cpp $L/Event.h 
		echo Event.o succesfully made !
		g++ -c $L/Event.cpp -o $O/Event.o -I $L -Wall -Wextra

$O/Timing.o:	$L/Timing.cpp $L/Timing.h
		echo Timing.o succesfully made !
		g++ -c $L/Timing.cpp -o $O/Timing.o -I $L

$O/Temps.o:	$L/Temps.cpp $L/Temps.h
		echo Temps.o succesfully made !
		g++ -c $L/Temps.cpp -o $O/Temps.o -I $L

$O/planifiable.o:	$L/planifiable.cpp $L/planifiable.h
		echo planifiable.o succesfully made !
		g++ -c $L/planifiable.cpp -o $O/planifiable.o -I $L

$O/Professeur.o:	$L/Professeur.cpp $L/Professeur.h 
		echo Professeur.o succesfully made !
		g++ -c $L/Professeur.cpp -o $O/Professeur.o -I $L

$O/Groupe.o:	$L/Groupe.cpp $L/Groupe.h
		echo Groupe.o succesfully made !
		g++ -c $L/Groupe.cpp -o $O/Groupe.o -I $L

$O/Local.o:	$L/Local.cpp $L/Local.h
		echo Local.o succesfully made !
		g++ -c $L/Local.cpp -o $O/Local.o -I $L

$O/Exception.o:	$L/Exception.cpp $L/Exception.h
		echo Exception.o succesfully made !
		g++ -c $L/Exception.cpp -o $O/Exception.o -I $L

$O/TempsException.o:	$L/TempsException.cpp $L/TempsException.h
		echo TempsException.o succesfully made !
		g++ -c $L/TempsException.cpp -o $O/TempsException.o -I $L

$O/TimingException.o:	$L/TimingException.cpp $L/TimingException.h
		echo TimingException.o succesfully made !
		g++ -c $L/TimingException.cpp -o $O/TimingException.o -I $L


$O/Liste.o:	$L/Liste.cpp $L/Liste.h
		echo Liste.o succesfully made !
		g++ -c $L/Liste.cpp -o $O/Liste.o -I $L -Wall -Wextra

$O/ListeTriee.o:	$L/ListeTriee.cpp $L/ListeTriee.h $O/Cours.o
		echo ListeTriee.o succesfully made !
		g++ -c $L/ListeTriee.cpp -o $O/ListeTriee.o  -I $L

$O/Iterateur.o:	$L/Iterateur.cpp $L/Iterateur.h
		echo Iterateur.o succesfully made !
		g++ -c $L/Iterateur.cpp -o $O/Iterateur.o -I $L -Wall -Wextra


$O/Horaire.o:	$L/Horaire.cpp $L/Horaire.h $O/Cours.o $O/Iterateur.o
			echo horaire.o succesfully made !
			g++ -c $L/Horaire.cpp -o $O/Horaire.o -I $L -Wall -Wextra

$O/Cours.o:	$L/Cours.cpp $L/Cours.h $O/Event.o $O/Liste.o
			echo Cours.o succesfully made !
			g++ -c $L/Cours.cpp -o $O/Cours.o -I $L -Wall -Wextra

	
clean: 
	rm -rf ./object/*.o