#if !defined(INCLUDED_CAPTURE_THREE)
#define INCLUDED_CAPTURE_THREE

typedef struct CaptureList
{
    int position[2];
    struct CaptureList *previous;
    struct CaptureList *next;
} CaptureList;

void FreeCaptureList(CaptureList *gameThree);
CaptureList *CreateCaptureList(const int position[2],
                                 const CaptureList *previous);

#endif // INCLUDED_CAPTURE_THREE