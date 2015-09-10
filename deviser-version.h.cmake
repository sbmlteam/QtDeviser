#ifndef DEVISER_VERSION_H
#define DEVISER_VERSION_H

/**
 * DEVISER_DOTTED_VERSION:
 *
 * A version string of the form "1.2.3".
 */
#define DEVISER_DOTTED_VERSION	"@PACKAGE_VERSION@"


/**
 * DEVISER_VERSION:
 *
 * The version as an integer: version 1.2.3 becomes 10203.  Since the major
 * number comes first, the overall number will always increase when a new
 * QtDeviser is released, making it easy to use less-than and greater-than
 * comparisons when testing versions numbers.
 */
#define DEVISER_VERSION		@DEVISER_VERSION_NUMERIC@


/**
 * DEVISER_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define DEVISER_VERSION_STRING	"@DEVISER_VERSION_NUMERIC@"


#endif // DEVISER_VERSION_H

