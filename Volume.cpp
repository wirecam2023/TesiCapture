#include "stdafx.h"
#include "Endox.h"
#include <winioctl.h>
#include "Volume.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE OpenDiskHandle(LPCSTR szDriveName,
                      INT iTotTentativi)
{
    HANDLE hDisk = INVALID_HANDLE_VALUE;
    INT iTentativi = 0;
    CString strDrive;

    strDrive.Format("\\\\.\\%s:",
                    szDriveName);

    while ((hDisk == INVALID_HANDLE_VALUE) &&
           (iTentativi < iTotTentativi)) {
        iTentativi++;

        hDisk = CreateFile(strDrive,
                           GENERIC_READ | GENERIC_WRITE,
                           FILE_SHARE_READ | FILE_SHARE_WRITE, //servono per il LOCK e per il DISMOUNT...
                           NULL, //&secAttr,
                           OPEN_EXISTING,
                           0,
                           NULL);
    }

    return hDisk;
}


void CloseDiskHandle(HANDLE hDisk)
{
    if (hDisk != INVALID_HANDLE_VALUE)
        CloseHandle(hDisk);
}


BOOL LockVolume(HANDLE hDisk)
{
    DWORD dwReturnedByteCount;

    return DeviceIoControl(hDisk,
                           FSCTL_LOCK_VOLUME,
                           NULL,
                           0,
                           NULL,
                           0,
                           &dwReturnedByteCount,
                           NULL);
}


BOOL UnlockVolume(HANDLE hDisk)
{
    DWORD dwReturnedByteCount;

    return DeviceIoControl(hDisk,
                           FSCTL_UNLOCK_VOLUME,
                           NULL,
                           0,
                           NULL,
                           0,
                           &dwReturnedByteCount,
                           NULL);
}


BOOL DismountVolume(HANDLE hDisk)
{
    DWORD dwReturnedByteCount;

    return DeviceIoControl(hDisk,
                           FSCTL_DISMOUNT_VOLUME,
                           NULL,
                           0,
                           NULL,
                           0,
                           &dwReturnedByteCount,
                           NULL);
}

int GetMediaType(HANDLE hDisk)
{
    DISK_GEOMETRY SupportedGeometry;
    DWORD dwReturnedByteCount;

    if (DeviceIoControl(hDisk,
                        IOCTL_DISK_GET_DRIVE_GEOMETRY,
                        NULL,
                        0,
                        &SupportedGeometry,
                        sizeof(SupportedGeometry),
                        &dwReturnedByteCount,
                        NULL))
        return SupportedGeometry.MediaType;

    return -1;

    //F5_1Pt2_512		//MediaType = "5.25, 1.2MB,  512 bytes/sector"
    //F3_1Pt44_512		//MediaType = "3.5,  1.44MB, 512 bytes/sector"
    //F3_2Pt88_512		//MediaType = "3.5,  2.88MB, 512 bytes/sector"
    //F3_20Pt8_512		//MediaType = "3.5,  20.8MB, 512 bytes/sector"
    //F3_720_512		//MediaType = "3.5,  720KB,  512 bytes/sector"
    //F5_360_512		//MediaType = "5.25, 360KB,  512 bytes/sector"
    //F5_320_512		//MediaType = "5.25, 320KB,  512 bytes/sector"
    //F5_320_1024		//MediaType = "5.25, 320KB,  1024 bytes/sector"
    //F5_180_512		//MediaType = "5.25, 180KB,  512 bytes/sector"
    //F5_160_512		//MediaType = "5.25, 160KB,  512 bytes/sector"
    //RemovableMedia	//MediaType = "Removable media other than floppy"
    //FixedMedia		//MediaType = "Fixed hard disk media"
}


BOOL SetEjectableMedia(HANDLE hDisk,
                       BOOL bRemoval)
{
    PREVENT_MEDIA_REMOVAL InMediaRemoval;
    DWORD dwReturnedByteCount;

    InMediaRemoval.PreventMediaRemoval = !bRemoval;

    return DeviceIoControl(hDisk,
                           IOCTL_DISK_MEDIA_REMOVAL,
                           &InMediaRemoval,
                           sizeof(InMediaRemoval),
                           NULL,
                           0,
                           &dwReturnedByteCount,
                           NULL);
}


BOOL EjectVolume(HANDLE hDisk)
{
    DWORD dwReturnedByteCount;

    return DeviceIoControl(hDisk,
                           IOCTL_DISK_EJECT_MEDIA,
                           NULL,
                           0,
                           NULL,
                           0,
                           &dwReturnedByteCount,
                           NULL);
}


BOOL EjectThisDisk(const CString &strDisk) 
{
    HANDLE hDisk = OpenDiskHandle(strDisk.Left(1), 2);
    BOOL bEjected = FALSE;

    if (hDisk != INVALID_HANDLE_VALUE)
	{
        BOOL bESC = FALSE;

        while(!bESC)
		{
            LockVolume(hDisk);
            SetEjectableMedia(hDisk, TRUE);
            bESC = EjectVolume(hDisk);
            UnlockVolume(hDisk);
            DismountVolume(hDisk);

            if (bESC)
                bEjected = TRUE;
			else
				bESC = (theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_VOLUME_EJECT_FAILED), MB_YESNO) == IDNO);
        }

        CloseDiskHandle(hDisk);
    }
	else
	{
		theApp.AfxMessageBoxEndo(theApp.GetMessageString(IDS_VOLUME_EJECT_NO_DISK));
    }

    return bEjected;
}
