/*
 * add by armite@126.com
 */

#ifdef __cplusplus
extern "C" {
#endif

void startCVM(char *url);

typedef void (*getBitmap)(int width, int height, int *stride, void **data);
typedef void (*refreshBitmap)();
typedef void (*releaseBitmap)();
void setBitmapFuns(getBitmap g, refreshBitmap f, releaseBitmap l);

#ifdef __cplusplus
}
#endif





