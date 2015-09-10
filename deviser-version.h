#ifndef DEVISER_VERSION_H
#define DEVISER_VERSION_H

/**
 * DEVISER_DOTTED_VERSION:
 *
 * A version string of the form "1.2.3".
 */
#define DEVISER_DOTTED_VERSION	"1.0.0"


/**
 * DEVISER_VERSION:
 *
 * The version as an integer: version 1.2.3 becomes 10203.  Since the major
 * number comes first, the overall number will always increase when a new
 * QtDeviser is released, making it easy to use less-than and greater-than
 * comparisons when testing versions numbers.
 */
#define DEVISER_VERSION		10000


/**
 * DEVISER_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define DEVISER_VERSION_STRING	"10000"


#endif // DEVISER_VERSION_H

