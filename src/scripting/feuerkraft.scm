;; This file contains a bunch of overrides of exported functions to
;; make there handling easier on the scheme side, the C version is
;; still accessible via the 'c:' prefix.

(display "### Loading helper function...")(newline)

(define c:comm-send-message comm-send-message)
(define c:building-create-type building-create-type)

(define (comm-send-message color . msg)
  (c:comm-send-message color (call-with-output-string 
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

;; EOF ;;