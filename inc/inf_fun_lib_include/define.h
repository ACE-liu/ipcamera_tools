//typedef int BOOL;
#ifndef BOOL
#define BOOL int
#endif

#ifndef DB
#define DB(x)				\
	printf("%s\n", x);
#endif

#define  TRUE  1
#define  FALSE 0

//MARCO define
#define SAFE_DELETE(p)  { if(p != NULL) { delete (p);     (p) = NULL; } }   //Delete object by New create 
#define SAFE_DELETEA(p) { if(p != NULL) { delete[] (p);   (p) = NULL; } }   //Delete Arrary
#define SAFE_RELEASE(p) { if(p != NULL) { (p)->Release(); (p) = NULL; } }
#define SAFE_FREE(p)	{ if(p != NULL) { free(p); (p) = NULL; } }
