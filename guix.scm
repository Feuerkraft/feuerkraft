;; Feuerkraft - A Tank Battle Game
;; Copyright (C) 2019 Ingo Ruhnke <grumbel@gmail.com>
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

(use-modules (ice-9 popen)
             (ice-9 rdelim)
             (guix build utils)
             (guix build-system gnu)
             (guix build-system cmake)
             (guix git-download)
             (guix gexp)
             (guix licenses)
             (guix packages)
             (gnu packages guile)
             (gnu packages linux)
             (gnu packages autotools)
             (gnu packages compression)
             (gnu packages gl)
             (gnu packages pkg-config)
             (gnu packages image)
             (gnu packages sdl)
             (gnu packages bdw-gc)
             (gnu packages swig)
             (gnu packages xiph)
             (gnu packages xorg))

(define %source-dir (dirname (current-filename)))

(define current-commit
  (with-directory-excursion %source-dir
                            (let* ((port   (open-input-pipe "git describe --tags"))
                                   (output (read-line port)))
                              (close-pipe port)
                              (string-trim-right output #\newline))))

(define-public clanlib-1.0
  (package
   (name "clanlib-1.0")
   (version "1.0")
   (source (origin
            (method git-fetch)
            (uri (git-reference
                  (url "https://gitlab.com/grumbel/clanlib-1.0.git")
                  (commit "0c41f22")))
            (file-name (git-file-name name version))
            (sha256
             (base32
              "0hdrvgs7fzrz4cmyjq9zxqj17zanwadrwpd8dmqcd8bin43c56qf"))))
   (build-system gnu-build-system)
   (native-inputs
    `(("autoconf" ,autoconf)
      ("automake" ,automake)
      ("libtool" ,libtool)
      ("pkg-config" ,pkg-config)))
   (inputs
    `(("libpng" ,libpng)
      ("libjpeg" ,libjpeg)
      ("sdl" ,sdl)
      ;;("sdl-image" ,sdl-image)
      ;;("sdl-mixer" ,sdl-mixer)
      ("sdl-gfx" ,sdl-gfx)
      ("libmikmod" ,libmikmod)
      ("libvorbis" ,libvorbis)
      ("libogg" ,libogg)
      ("libxi" ,libxi)
      ("libxmu" ,libxmu)
      ("alsa-lib" ,alsa-lib)
      ("mesa" ,mesa)
      ("glu" ,glu)))
   (arguments
    `(#:tests? #f
      #:configure-flags '("--disable-docs")))
   (synopsis "ClanLib game SDK development files")
   (description "ClanLib is a multi-platform software development kit,
with an emphasis on game development.

On one side, it tries to provide a platform independent interface to
write games with, by taking over the low-level work from the game and
providing wrappers around toolkits such as DirectFB, DirectX, OpenGL,
Vorbis, X11, etc., so that if a game is written with ClanLib, the game
should compile on any platform supported by ClanLib without changing
its source code.

On the other hand, ClanLib also tries to be a service-minded SDK.  In
other words, the developers have put great effort into designing the
API, to ensure ClanLib's ease of use - while maintaining its power.

This is the development part of the ClanLib SDK, which is needed to
build applications with it.")
   (home-page "https://gitlab.com/grumbel/clanlib-1.0/")
   (license zlib)))

(define-public feuerkraft
  (package
   (name "feuerkraft")
   (version current-commit)
   (source (local-file %source-dir
                       #:recursive? #t
                       #:select? (git-predicate %source-dir)))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f  ; some swig dependency issue
      ))
   (native-inputs
    `(("pkg-config" ,pkg-config)))
   (inputs
    `(("mesa" ,mesa)
      ("glu" ,glu)
      ("swig" ,swig)
      ("guile-2.2" ,guile-2.2)
      ("libatomic-ops" ,libatomic-ops)
      ("clanlib-1.0" ,clanlib-1.0)))
   (synopsis "A Tank Battle Game")
   (description "Feuerkraft is an incomplete 2D top-down tank battle
game with some inspiration from games like GTA or Operation
Flashpoint.  It is not in a playable state, but it allows you to run
around and get into vehicles.")
   (home-page "https://feuerkraft.gitlab.io")
   (license gpl3+)))

feuerkraft

;; EOF ;;
