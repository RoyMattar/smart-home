#	root makefile

check: mvp registration listing distribution complete simulation

mvp:
	@$(MAKE) -C tests/mvp_test check
registration:
	@$(MAKE) -C tests/registration_test check
listing:
	@$(MAKE) -C tests/listing_test check
distribution:
	@$(MAKE) -C tests/distribution_test check
complete:
	@$(MAKE) -C tests/complete_test check
simulation:
	@$(MAKE) -C tests/simulation check

clean: clean_tests_mvp \
	   clean_tests_registration clean_tests_listing clean_tests_distribution \
	   clean_tests_complete clean_tests_simulation

clean_tests_mvp:
	@$(MAKE) -C tests/mvp_test clean
clean_tests_registration:
	@$(MAKE) -C tests/registration_test clean
clean_tests_listing:
	@$(MAKE) -C tests/listing_test clean
clean_tests_distribution:
	@$(MAKE) -C tests/distribution_test clean
clean_tests_complete:
	@$(MAKE) -C tests/complete_test clean
clean_tests_simulation:
	@$(MAKE) -C tests/simulation clean

.PHONY: check mvp registration listing distribution complete simulation \
		clean clean_src clean_tests_src clean_tests_mvp \
		clean_tests_registration clean_tests_listing clean_tests_distribution \
		clean_tests_complete clean_tests_simulation