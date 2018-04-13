#include <memory>
#include "nbind/api.h"
#include "control.h"
#include "ui.h"

class UiSpinbox : public UiControl {

  public:
	DEFINE_EVENT(onChanged)

	UiSpinbox(int min, int max);
	UiSpinbox();
	~UiSpinbox();
	DEFINE_CONTROL_METHODS()

	int getValue();
	void setValue(int value);
	void onDestroy(uiControl *control) override;
};

void UiSpinbox::onDestroy(uiControl *control) {
	/*
		freeing event callbacks to allow JS to garbage collect this class
		when there are no references to it left in JS code.
	*/

	delete onChangedCallback;
	onChangedCallback = nullptr;
}

UiSpinbox::UiSpinbox(int min, int max)
	: UiControl((uiControl *)uiNewSpinbox(min, max)) {}

UiSpinbox::UiSpinbox() : UiControl((uiControl *)uiNewSpinbox(0, 100)) {}

int UiSpinbox::getValue() {
	return uiSpinboxValue((uiSpinbox *)getHandle());
}

void UiSpinbox::setValue(int value) {
	uiSpinboxSetValue((uiSpinbox *)getHandle(), value);
	if (onChangedCallback != nullptr) {
		(*onChangedCallback)();
	}
}

IMPLEMENT_EVENT(UiSpinbox, uiSpinbox, onChanged, uiSpinboxOnChanged)

INHERITS_CONTROL_METHODS(UiSpinbox)

NBIND_CLASS(UiSpinbox) {
	construct<int, int>();
	construct<>();
	DECLARE_CHILD_CONTROL_METHODS()
	getset(getValue, setValue);
	method(getValue);
	method(setValue);
	method(onChanged);
}
