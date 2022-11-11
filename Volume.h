#ifndef __VOLUME_H__
	#define __VOLUME_H__

extern HANDLE OpenDiskHandle(LPCSTR szDriveName, INT nTotTentativi);
extern void CloseDiskHandle(HANDLE hDisk);

extern BOOL LockVolume(HANDLE hDisk);
extern BOOL UnlockVolume(HANDLE hDisk);

extern BOOL DismountVolume(HANDLE hDisk);

extern INT GetMediaType(HANDLE hDisk);

extern BOOL SetEjectableMedia(HANDLE hDisk, BOOL bRemoval);
extern BOOL EjectVolume(HANDLE hDisk);
extern BOOL EjectThisDisk(const CString &strDisk);


#endif  /* __VOLUME_H__ */
