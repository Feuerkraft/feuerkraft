#!/usr/bin/guile \
-e main -s
!#

(load "helper.scm")

(define (get-images-lst)
  (filter (lambda (filename)
	    (equal? (stat:type (stat (string-append "images/tiles/" filename))) 'regular))
	  (directory->list "images/tiles/")))

(define (main args)
  (println "section tiles {")
  (for-each (lambda (filename)
	      (println "	" (substring filename 0 (- (string-length filename) 4)) 
		       " = (type=sprite, image1=images/tiles/" filename ");"))
	    (sort (get-images-lst) string<=?))
  (println "}")
  (newline))

;; EOF ;;