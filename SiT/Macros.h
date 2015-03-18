#define NS_SIT_BEGIN                     namespace SiT {
#define NS_SIT_END                       }
#define USING_NS_SIT                     using namespace SiT;

//#if defined(_USRDLL)
//    #define SIT_DLL     __declspec(dllexport)
//#else         /* use a DLL library */
//    #define SIT_DLL     __declspec(dllimport)
//#endif

#define SIT_DLL

#define LOG(format, ...) printf(format, ##__VA_ARGS__)

#define PI 3.14159265358979323846
