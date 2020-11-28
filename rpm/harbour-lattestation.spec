# 
# Do NOT Edit the Auto-generated Part!
# Generated by: spectacle version 0.32
# 

Name:       harbour-lattestation

# >> macros
%define __provides_exclude_from ^%{_datadir}/.*$
%define __requires_exclude ^libjpeg.*|libpoppler.*|libpoppler-qt5.*|libnspr4.*|libnss3.*|libopenjp2.*|libplc4.*|libplds4.*|libsmime3.*|libfreetype.*|libjpeg.*|libfreetype.*|libnssutil3.*$
%{?qtc_builddir:%define _builddir %qtc_builddir}
# << macros

Summary:    L'Attestation de Sortie
Version:    0.4
Release:    1
Group:      Qt/Qt
License:    GPLv3
URL:        http://github.com/JulienBlanc-tgcm/LAttestation
Source0:    %{name}-%{version}.tar.bz2
Source100:  harbour-lattestation.yaml
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(poppler-qt5)
BuildRequires:  desktop-file-utils

%description
Un générateur d’attestation de sortie...


%prep
%setup -q -n %{name}-%{version}

# >> setup
# << setup

%build
# >> build pre
# << build pre

%qmake5 

make %{?_smp_mflags}

# >> build post
# << build post

%install
rm -rf %{buildroot}
# >> install pre
# << install pre
%qmake5_install

# >> install post
install -d %{buildroot}/usr/share/%{name}/lib
install -m 644 -p /usr/lib/libpoppler.so.85 %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libpoppler-qt5.so.1 %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libfreetype.so.6 %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libopenjp2.so.7 %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libsmime3.so %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libnspr4.so %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libnss3.so %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libnssutil3.so %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libplc4.so %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libplds4.so %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libjpeg.so.62 %{buildroot}/usr/share/%{name}/lib/
install -m 644 -p /usr/lib/libopenjp2.so.7 %{buildroot}/usr/share/%{name}/lib/
# << install post

desktop-file-install --delete-original       \
  --dir %{buildroot}%{_datadir}/applications             \
   %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
# >> files
# << files

%changelog
* Sat Nov 28 2020 - Julien Blanc <julien.blanc@tgcm.eu> 0.4-1
- update of the pdf file model
- can now select multiple motives
- improved deletion of old certificates
* Fri Nov 13 2020 - Julien Blanc <julien.blanc@tgcm.eu> 0.3-1
- version en Frenglish
- ajout de l’heure courante sur la page de génération
- mode « oups » (optionnel)

