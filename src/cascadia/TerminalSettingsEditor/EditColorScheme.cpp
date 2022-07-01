// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#include "pch.h"
#include "EditColorScheme.h"
#include "EditColorScheme.g.cpp"

#include <LibraryResources.h>

using namespace winrt;
using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Navigation;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt
{
    namespace MUX = Microsoft::UI::Xaml;
    namespace WUX = Windows::UI::Xaml;
}

namespace winrt::Microsoft::Terminal::Settings::Editor::implementation
{
    EditColorScheme::EditColorScheme()
    {
        InitializeComponent();
    }

    void EditColorScheme::OnNavigatedTo(const NavigationEventArgs& e)
    {
        _ViewModel = e.Parameter().as<Editor::ColorSchemeViewModel>();
    }

    void EditColorScheme::ColorPickerChanged(const IInspectable& sender,
                                          const MUX::Controls::ColorChangedEventArgs& args)
    {
        const til::color newColor{ args.NewColor() };
        if (const auto& picker{ sender.try_as<MUX::Controls::ColorPicker>() })
        {
            if (const auto& tag{ picker.Tag() })
            {
                if (const auto index{ tag.try_as<uint8_t>() })
                {
                    if (index < ColorTableDivider)
                    {
                        _ViewModel.NonBrightColorTable().GetAt(*index).Color(newColor);
                    }
                    else
                    {
                        _ViewModel.BrightColorTable().GetAt(*index - ColorTableDivider).Color(newColor);
                    }
                }
                else if (const auto stringTag{ tag.try_as<hstring>() })
                {
                    if (stringTag == ForegroundColorTag)
                    {
                        _ViewModel.ForegroundColor().Color(newColor);
                    }
                    else if (stringTag == BackgroundColorTag)
                    {
                        _ViewModel.BackgroundColor().Color(newColor);
                    }
                    else if (stringTag == CursorColorTag)
                    {
                        _ViewModel.CursorColor().Color(newColor);
                    }
                    else if (stringTag == SelectionBackgroundColorTag)
                    {
                        _ViewModel.SelectionBackgroundColor().Color(newColor);
                    }
                }
            }
        }
    }

    void EditColorScheme::RenameAccept_Click(const IInspectable& /*sender*/, const RoutedEventArgs& /*e*/)
    {
        //_RenameCurrentScheme(NameBox().Text());
    }

    void EditColorScheme::RenameCancel_Click(const IInspectable& /*sender*/, const RoutedEventArgs& /*e*/)
    {
        //RenameErrorTip().IsOpen(false);
        //NameBox().Text(_ViewModel.CurrentScheme().Name());
    }

    void EditColorScheme::NameBox_PreviewKeyDown(const IInspectable& /*sender*/, const winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs& e)
    {
        if (e.OriginalKey() == winrt::Windows::System::VirtualKey::Enter)
        {
            //_RenameCurrentScheme(NameBox().Text());
            e.Handled(true);
        }
        else if (e.OriginalKey() == winrt::Windows::System::VirtualKey::Escape)
        {
            //RenameErrorTip().IsOpen(false);
            //NameBox().Text(_ViewModel.CurrentScheme().Name());
            e.Handled(true);
        }
    }

    void EditColorScheme::_RenameCurrentScheme(hstring newName)
    {
        //if (_ViewModel.RequestRenameCurrentScheme(newName))
        //{
        //    // update the UI
        //    //RenameErrorTip().IsOpen(false);

        //    // The color scheme is renamed appropriately, but the ComboBox still shows the old name (until you open it)
        //    // We need to manually force the ComboBox to refresh itself.
        //    const auto selectedIndex{ ColorSchemeListView().SelectedIndex() };
        //    ColorSchemeListView().SelectedIndex((selectedIndex + 1) % ViewModel().AllColorSchemes().Size());
        //    ColorSchemeListView().SelectedIndex(selectedIndex);

        //    //NameBox().Focus(FocusState::Programmatic);
        //}
        //else
        //{
        //    //RenameErrorTip().Target(NameBox());
        //    //RenameErrorTip().IsOpen(true);

        //    // focus the name box
        //    //NameBox().Focus(FocusState::Programmatic);
        //    //NameBox().SelectAll();
        //}
    }
}
