;; This file contains a bunch of overrides of exported functions to
;; make there handling easier on the scheme side, the C version is
;; still accessible via the 'c:' prefix.

(define *static-binary* #t)

;;(cond ((not *static-binary*)
;;       (use-modules (ice-9 readline))
;;       (activate-readline)))

(display "### Loading helper function...")(newline)

(define c:comm-send-message comm-send-message)
(define c:building-create-type building-create-type)

(define (comm-send-message color . msg)
  (c:comm-send-message 0 ;; FIXME: color 'node
                       (call-with-output-string 
                        (lambda (port)
                          (for-each (lambda (el)
                                      (display el port))
                                    msg)))))

(define (building-create-type name . args)
  (display "building-create-type: ")
  (display name)
  (display " -> ")
  (display args)(newline)
  (c:building-create-type name args))

(define (feuerkraft:repl)
  (display "### Feuerkraft repl, exit with (quit)\n")
  (let ((old-prompt scm-repl-prompt))
    (set-repl-prompt! "feuerkraft> ")
    (catch #t
           (lambda ()
             (top-repl)
             (display "Feuerkraft Readline exited nicly.\n"))
           (lambda args 
             (display "Error: ")
             (display args)(newline)))
    (set-repl-prompt! old-prompt)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Game Play related stuff ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define player-soldier 0)

(define (join-nearest-vehicle)
  (let ((obj (player-get-current-unit)))
    (cond ((gameobj-is-soldier obj)
           (let ((vehicle (vehicle-find-nearest 
                           (gameobj-get-property obj "x-pos")
                           (gameobj-get-property obj "y-pos")
                           50)))
             (cond ((not (= vehicle 0))
                    ;;(format #t "Found Vehicle: ~a~%" vehicle)
                    (player-set-current-unit vehicle)
                    (set! player-soldier obj)
                    (gameobj-set-property obj "hidden" #t)
                    (comm-send-message 'note "You entered vehicle " vehicle))
                   (else
                    (comm-send-message 'note "No vehicle around to enter")))
             ))
          (else
           (comm-send-message 'note "You left vehicle " obj)

           (let* ((orientation (- (gameobj-get-property obj "orientation") (/ 3.1415927 2.0)))
                  (x (* (cos orientation) 25))
                  (y (* (sin orientation) 25)))
             
             (gameobj-set-property player-soldier 
                                   "x-pos" (+ (gameobj-get-property obj "x-pos") x))
             (gameobj-set-property player-soldier
                                   "y-pos" (+ (gameobj-get-property obj "y-pos") y))
             (gameobj-set-property player-soldier
                                   "orientation" (+ (gameobj-get-property obj "orientation")
                                                    (/ 3.1415927 2.0)))

             (player-set-current-unit player-soldier)
             (gameobj-set-property player-soldier "hidden" #f))))))

(input-register-callback "key_k" join-nearest-vehicle)

(input-register-callback "key_f1" display-show-help)
(input-register-callback "key_f2" display-hide-help)

(input-register-callback "key_m" (lambda ()
                                   (if (display-levelmap-visible)
                                       (display-hide-levelmap)
                                       (display-show-levelmap))))

(input-register-callback "key_a" (lambda () 
                                   (format #t "Menu Visible: ~a~%" (menu-visible))
                                   (if (menu-visible)
                                       (menu-hide)
                                       (menu-show 0))))


;; EOF ;;