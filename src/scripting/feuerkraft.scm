(define comm-send-message-c comm-send-message)

(define (comm-send-message color . msg)
  (comm-send-message-c color (call-with-output-string 
                              (lambda (port)
                                (for-each (lambda (el)
                                            (display el port))
                                          msg)))))

;; EOF ;;