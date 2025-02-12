// Created by dorgon, All Rights Reserved.
// Date of intended publication: 2019/08/01
// email: dorgonman@hotmail.com
// blog: dorgon.horizon-studio.net

#include "Widget/Components/HorizonImage.h"
#include "HorizonUIPrivate.h"
UHorizonImage::UHorizonImage()
{
	UVRegion.bIsValid = true;
}


#if WITH_EDITOR

const FText UHorizonImage::GetPaletteCategory()
{
	return NSLOCTEXT("HorizonPlugin", "HorizonPlugin", "HorizonPlugin");
}





void UHorizonImage::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	

}
#endif //#if WITH_EDITOR

void UHorizonImage::SynchronizeProperties()
{
	Super::SynchronizeProperties();
#if UE_VERSION_OLDER_THAN(5,2,0)
	Brush.SetUVRegion(UVRegion);
#else
	FSlateBrush& slateBrush = const_cast<FSlateBrush&>(GetBrush());
	slateBrush.SetUVRegion(UVRegion);
#endif
}
