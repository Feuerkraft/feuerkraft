#!/usr/bin/guile \
-e main -s
!#

(load "helper.scm")

(define (get-images-lst)
  (filter (lambda (filename)
	    (equal? (stat:type (stat (string-append "tiles/" filename))) 'regular))
	  (directory->list "tiles/")))

(define (main args)
  (println "section tiles {")
  (for-each (lambda (filename)
	      (println "	section " (substring filename 0 (- (string-length filename) 4)) " {")
	      (println "		frame1 = images/tiles/" filename " (type=surface);")
	      (println "	}")
	      (newline))
	    (sort (get-images-lst) string<=?))
  (println "}")
  (newline))

;; EOF ;;