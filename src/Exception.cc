#include "Exception.h"

#include <string>

#include <ll/api/utils/ErrorUtils.h>


namespace TSEssential::Exception {


void ProcessException(std::exception_ptr ptr) {
    if (ptr) {
        try {
            std::rethrow_exception(ptr);
        } catch (const ll::error_utils::seh_exception& exc) {
            LOGGER.error("Exception(SEH_EXCEPTION) Message:");
            LOGGER.error(exc.what());
        }  catch (const std::exception& exc) {
            LOGGER.error("Exception(STD) Message:");
            LOGGER.error(exc.what());
        } catch (const std::string &str) {
            LOGGER.error("Exception(STRING) Content:");
            LOGGER.error(str);
        // } catch (const int &v) {
        //     LOGGER.error("Exception(int) Content:");
        //     LOGGER.error("{0}", v);
        } catch (...) {
            LOGGER.error("Abnormal info is not an abnormal type!");
        }
    } else {
        LOGGER.error("Unable to resolve exception!");
    }
}
} // namespace LL3Mine2_Class::Exception