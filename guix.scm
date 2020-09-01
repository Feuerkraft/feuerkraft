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

(set! %load-path
  (cons* "/ipfs/QmNbci3WpEWumBVvfbqsKhKnJTtdmkyVwYtSaPr5jVZo2m/guix-cocfree_0.0.0-56-g3a32b64"
         %load-path))

(use-modules (guix build-system cmake)
             ((guix licenses) #:prefix license:)
             (guix packages)
             (gnu packages guile)
             (gnu packages gl)
             (gnu packages pkg-config)
             (gnu packages swig)
             (guix-cocfree utils))

(define %source-dir (dirname (current-filename)))

(define clanlib-1.0
  (package-from-file
   "/ipfs/QmbZhaLZULD3EbKEdG4NnsVLgA9Jo2w7vt222aVryeWXkq/clanlib-1.0_1.0.0-18-gf0de815/guix.scm"))

(define-public feuerkraft
  (package
   (name "feuerkraft")
   (version (version-from-source %source-dir))
   (source (source-from-source %source-dir))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #f))  ; no tests
   (native-inputs
    `(("pkg-config" ,pkg-config)))
   (inputs
    `(("mesa" ,mesa)
      ("glu" ,glu)
      ("swig" ,swig)
      ("guile" ,guile-3.0)
      ("clanlib-1.0" ,clanlib-1.0)))
   (synopsis (synopsis-from-source %source-dir))
   (description (description-from-source %source-dir))
   (home-page (homepage-from-source %source-dir))
   (license license:gpl3+)))

feuerkraft

;; EOF ;;
