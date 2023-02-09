#pragma once

class OraeUtils
{
public:
	template <typename CompnentType>
	static CompnentType* GetSTUPlayerComponent(const AActor* Pawn)
	{
		return Pawn ? Cast<CompnentType>(Pawn->GetComponentByClass(CompnentType::StaticClass())) : nullptr;
	}
};
