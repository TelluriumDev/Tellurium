#include "./Exception.h"
#include "./TSEssential.h"
#include <string>


namespace LL3Mine2_Class::Exception {


void ProcessException(std::exception_ptr ptr) {
    if (ptr) {
        try {
            std::rethrow_exception(ptr);
        } catch (const std::exception& exc) {
            LOGGER.error("Exception Message:");
            LOGGER.error(exc.what());
        } catch (const std::string &str) {
            LOGGER.error("Exception(string) Content:");
            LOGGER.error(str);
        } catch (const int &v) {
            LOGGER.error("Exception(int) Content:");
            LOGGER.error("{0}", v);
        } catch (...) {
          LOGGER.error("Abnormal info is not an abnormal type!");
        }
    } else {
        LOGGER.error("Unable to resolve exception!");
    }
}
} // namespace LL3Mine2_Class::Exception