double data = .0; /* Initialize a data with 0 */

redEngineOn(config); /* Start the RED engine */
/* In this example, SpDCache is configured into three regions */
/* We can pass on a dynamic configuration to set the word granularity
   and the type of operation */

REG(IBR); /* Following reductions are processed by the DRC */

RED(&data, 1.); /* data += 1 */
RED(&data, 2.); /* data += 2 */

REG(OBR); /* Following reductions are processed by the SRT */

RED(&data, 3.); /* data += 3 */

redFlush(); /* The DRC and SRT are flushed to memory */

redEngineOff(); /* Stop the RED engine */
/* SpDCache is now back to one fully generic cache region */

printf("%lf", data); /* Should print 6 */