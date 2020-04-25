#	root makefile

check: mvp registration listing distribution

mvp:
	@$(MAKE) -C tests/mvptest check
registration:
	@$(MAKE) -C tests/registration_test check
listing:
	@$(MAKE) -C tests/listing_test check
distribution:
	@$(MAKE) -C tests/distribution_test check

clean: clean_tests_mvp \
	   clean_tests_registration clean_tests_listing clean_tests_distribution \
	   #clean_src clean_tests_src

clean_src:
	@$(MAKE) -C src clean
clean_tests_src:
	@$(MAKE) -C tests/src clean
clean_tests_mvp:
	@$(MAKE) -C tests/mvptest clean
clean_tests_registration:
	@$(MAKE) -C tests/registration_test clean
clean_tests_listing:
	@$(MAKE) -C tests/listing_test clean
clean_tests_distribution:
	@$(MAKE) -C tests/distribution_test clean

.PHONY: check mvp registration listing distribution \
		clean clean_src clean_tests_src clean_tests_mvp \
		clean_tests_registration clean_tests_listing clean_tests_distribution