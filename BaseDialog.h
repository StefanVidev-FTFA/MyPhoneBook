#pragma once

class CBaseDialog
{
public:
	CBaseDialog();
	virtual ~CBaseDialog();

};
enum DialogMode
{
	DialogModeView = 0,
	DialogModeEdit,
};