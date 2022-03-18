#pragma once

/// <summary>
/// Enumeration for virtual keys.
/// </summary>
enum class KeyCode : USHORT
{
    /// <summary>The Left (or primary) mouse button.</summary>
    Mouse0 = 0x01,
    /// <summary>The Right (or secondary) mouse button.</summary>
    Mouse1 = 0x02,
    /// <summary></summary>
    Cancel = 0x03,
    /// <summary>The Middle (or third) mouse button.</summary>
    Mouse2 = 0x04,

    /// <summary></summary>
    ExtraButton1 = 0x05,
    /// <summary></summary>
    ExtraButton2 = 0x06,
    /// <summary></summary>
    Back = 0x08,
    /// <summary></summary>
    Tab = 0x09,
    /// <summary></summary>
    Clear = 0x0C,
    /// <summary></summary>
    Return = 0x0D,
    /// <summary></summary>
    Shift = 0x10,
    /// <summary></summary>
    Control = 0x11,
    /// <summary></summary>
    Menu = 0x12,
    /// <summary></summary>
    Pause = 0x13,
    /// <summary></summary>
    CapsLock = 0x14,

    /// <summary></summary>
    Kana = 0x15,
    /// <summary></summary>
    Hangeul = 0x15,
    /// <summary></summary>
    Hangul = 0x15,
    /// <summary></summary>
    Junja = 0x17,
    /// <summary></summary>
    Final = 0x18,
    /// <summary></summary>
    Hanja = 0x19,
    /// <summary></summary>
    Kanji = 0x19,
    /// <summary></summary>
    Escape = 0x1B,
    /// <summary></summary>
    Convert = 0x1C,
    /// <summary></summary>
    NonConvert = 0x1D,
    /// <summary></summary>
    Accept = 0x1E,
    /// <summary></summary>
    ModeChange = 0x1F,

    /// <summary></summary>
    Space = 0x20,
    /// <summary></summary>
    Prior = 0x21,
    /// <summary></summary>
    Next = 0x22,
    /// <summary></summary>
    End = 0x23,
    /// <summary></summary>
    Home = 0x24,
    /// <summary></summary>
    Left = 0x25,
    /// <summary></summary>
    Up = 0x26,
    /// <summary></summary>
    Right = 0x27,
    /// <summary></summary>
    Down = 0x28,
    /// <summary></summary>
    Select = 0x29,
    /// <summary></summary>
    Print = 0x2A,
    /// <summary></summary>
    Execute = 0x2B,
    /// <summary></summary>
    Snapshot = 0x2C,
    /// <summary></summary>
    Insert = 0x2D,
    /// <summary></summary>
    Delete = 0x2E,
    /// <summary></summary>
    Help = 0x2F,

    /// <summary>The '0' key on the top of the alphanumeric keyboard.</summary>
    Alpha0 = 0x30,
    /// <summary>The '1' key on the top of the alphanumeric keyboard.</summary>
    Alpha1 = 0x31,
    /// <summary>The '2' key on the top of the alphanumeric keyboard.</summary>
    Alpha2 = 0x32,
    /// <summary>The '3' key on the top of the alphanumeric keyboard.</summary>
    Alpha3 = 0x33,
    /// <summary>The '4' key on the top of the alphanumeric keyboard.</summary>
    Alpha4 = 0x34,
    /// <summary>The '5' key on the top of the alphanumeric keyboard.</summary>
    Alpha5 = 0x35,
    /// <summary>The '6' key on the top of the alphanumeric keyboard.</summary>
    Alpha6 = 0x36,
    /// <summary>The '7' key on the top of the alphanumeric keyboard.</summary>
    Alpha7 = 0x37,
    /// <summary>The '8' key on the top of the alphanumeric keyboard.</summary>
    Alpha8 = 0x38,
    /// <summary>The '9' key on the top of the alphanumeric keyboard.</summary>
    Alpha9 = 0x39,

    /// <summary></summary>
    A = 0x41,
    /// <summary></summary>
    B = 0x42,
    /// <summary></summary>
    C = 0x43,
    /// <summary></summary>
    D = 0x44,
    /// <summary></summary>
    E = 0x45,
    /// <summary></summary>
    F = 0x46,
    /// <summary></summary>
    G = 0x47,
    /// <summary></summary>
    H = 0x48,
    /// <summary></summary>
    I = 0x49,
    /// <summary></summary>
    J = 0x4A,
    /// <summary></summary>
    K = 0x4B,
    /// <summary></summary>
    L = 0x4C,
    /// <summary></summary>
    M = 0x4D,
    /// <summary></summary>
    N = 0x4E,
    /// <summary></summary>
    O = 0x4F,
    /// <summary></summary>
    P = 0x50,
    /// <summary></summary>
    Q = 0x51,
    /// <summary></summary>
    R = 0x52,
    /// <summary></summary>
    S = 0x53,
    /// <summary></summary>
    T = 0x54,
    /// <summary></summary>
    U = 0x55,
    /// <summary></summary>
    V = 0x56,
    /// <summary></summary>
    W = 0x57,
    /// <summary></summary>
    X = 0x58,
    /// <summary></summary>
    Y = 0x59,
    /// <summary></summary>
    Z = 0x5A,

    /// <summary></summary>
    LeftWindows = 0x5B,
    /// <summary></summary>
    RightWindows = 0x5C,
    /// <summary></summary>
    Application = 0x5D,
    /// <summary></summary>
    Sleep = 0x5F,

    /// <summary></summary>
    Keypad0 = 0x60,
    /// <summary></summary>
    Keypad1 = 0x61,
    /// <summary></summary>
    Keypad2 = 0x62,
    /// <summary></summary>
    Keypad3 = 0x63,
    /// <summary></summary>
    Keypad4 = 0x64,
    /// <summary></summary>
    Keypad5 = 0x65,
    /// <summary></summary>
    Keypad6 = 0x66,
    /// <summary></summary>
    Keypad7 = 0x67,
    /// <summary></summary>
    Keypad8 = 0x68,
    /// <summary></summary>
    Keypad9 = 0x69,
    /// <summary>Numeric keypad '*'.</summary>
    KeypadMultiply = 0x6A,
    /// <summary>Numeric keypad '+'.</summary>
    KeypadPlus = 0x6B,
    /// <summary></summary>
    Separator = 0x6C,
    /// <summary>Numeric keypad '-'.</summary>
    KeypadMinus = 0x6D,
    /// <summary>Numeric keypad '.'.</summary>
    KeypadPeriod = 0x6E,
    /// <summary>Numeric keypad '/'.</summary>
    KeypadDivide = 0x6F,

    /// <summary></summary>
    F1 = 0x70,
    /// <summary></summary>
    F2 = 0x71,
    /// <summary></summary>
    F3 = 0x72,
    /// <summary></summary>
    F4 = 0x73,
    /// <summary></summary>
    F5 = 0x74,
    /// <summary></summary>
    F6 = 0x75,
    /// <summary></summary>
    F7 = 0x76,
    /// <summary></summary>
    F8 = 0x77,
    /// <summary></summary>
    F9 = 0x78,
    /// <summary></summary>
    F10 = 0x79,
    /// <summary></summary>
    F11 = 0x7A,
    /// <summary></summary>
    F12 = 0x7B,
    /// <summary></summary>
    F13 = 0x7C,
    /// <summary></summary>
    F14 = 0x7D,
    /// <summary></summary>
    F15 = 0x7E,
    /// <summary></summary>
    F16 = 0x7F,
    /// <summary></summary>
    F17 = 0x80,
    /// <summary></summary>
    F18 = 0x81,
    /// <summary></summary>
    F19 = 0x82,
    /// <summary></summary>
    F20 = 0x83,
    /// <summary></summary>
    F21 = 0x84,
    /// <summary></summary>
    F22 = 0x85,
    /// <summary></summary>
    F23 = 0x86,
    /// <summary></summary>
    F24 = 0x87,

    /// <summary></summary>
    NumLock = 0x90,
    /// <summary></summary>
    ScrollLock = 0x91,
    /// <summary></summary>
    NEC_Equal = 0x92,
    /// <summary></summary>
    Fujitsu_Jisho = 0x92,
    /// <summary></summary>
    Fujitsu_Masshou = 0x93,
    /// <summary></summary>
    Fujitsu_Touroku = 0x94,
    /// <summary></summary>
    Fujitsu_Loya = 0x95,
    /// <summary></summary>
    Fujitsu_Roya = 0x96,

    /// <summary></summary>
    LeftShift = 0xA0,
    /// <summary></summary>
    RightShift = 0xA1,
    /// <summary></summary>
    LeftControl = 0xA2,
    /// <summary></summary>
    RightControl = 0xA3,
    /// <summary></summary>
    LeftMenu = 0xA4,
    /// <summary></summary>
    RightMenu = 0xA5,
    /// <summary></summary>
    BrowserBack = 0xA6,
    /// <summary></summary>
    BrowserForward = 0xA7,
    /// <summary></summary>
    BrowserRefresh = 0xA8,
    /// <summary></summary>
    BrowserStop = 0xA9,
    /// <summary></summary>
    BrowserSearch = 0xAA,
    /// <summary></summary>
    BrowserFavorites = 0xAB,
    /// <summary></summary>
    BrowserHome = 0xAC,
    /// <summary></summary>
    VolumeMute = 0xAD,
    /// <summary></summary>
    VolumeDown = 0xAE,
    /// <summary></summary>
    VolumeUp = 0xAF,
    /// <summary></summary>
    MediaNextTrack = 0xB0,
    /// <summary></summary>
    MediaPrevTrack = 0xB1,
    /// <summary></summary>
    MediaStop = 0xB2,
    /// <summary></summary>
    MediaPlayPause = 0xB3,
    /// <summary></summary>
    LaunchMail = 0xB4,
    /// <summary></summary>
    LaunchMediaSelect = 0xB5,
    /// <summary></summary>
    LaunchApplication1 = 0xB6,
    /// <summary></summary>
    LaunchApplication2 = 0xB7,

    /// <summary></summary>
    OEM1 = 0xBA,
    /// <summary></summary>
    OEMPlus = 0xBB,
    /// <summary></summary>
    OEMComma = 0xBC,
    /// <summary></summary>
    OEMMinus = 0xBD,
    /// <summary></summary>
    OEMPeriod = 0xBE,
    /// <summary></summary>
    OEM2 = 0xBF,
    /// <summary></summary>
    OEM3 = 0xC0,
    /// <summary></summary>
    OEM4 = 0xDB,
    /// <summary></summary>
    OEM5 = 0xDC,
    /// <summary></summary>
    OEM6 = 0xDD,
    /// <summary></summary>
    OEM7 = 0xDE,
    /// <summary></summary>
    OEM8 = 0xDF,
    /// <summary></summary>
    OEMAX = 0xE1,
    /// <summary></summary>
    OEM102 = 0xE2,
    /// <summary></summary>
    ICOHelp = 0xE3,
    /// <summary></summary>
    ICO00 = 0xE4,
    /// <summary></summary>
    ProcessKey = 0xE5,
    /// <summary></summary>
    ICOClear = 0xE6,
    /// <summary></summary>
    Packet = 0xE7,
    /// <summary></summary>
    OEMReset = 0xE9,
    /// <summary></summary>
    OEMJump = 0xEA,
    /// <summary></summary>
    OEMPA1 = 0xEB,
    /// <summary></summary>
    OEMPA2 = 0xEC,
    /// <summary></summary>
    OEMPA3 = 0xED,
    /// <summary></summary>
    OEMWSCtrl = 0xEE,
    /// <summary></summary>
    OEMCUSel = 0xEF,
    /// <summary></summary>
    OEMATTN = 0xF0,
    /// <summary></summary>
    OEMFinish = 0xF1,
    /// <summary></summary>
    OEMCopy = 0xF2,
    /// <summary></summary>
    OEMAuto = 0xF3,
    /// <summary></summary>
    OEMENLW = 0xF4,
    /// <summary></summary>
    OEMBackTab = 0xF5,
    /// <summary></summary>
    ATTN = 0xF6,
    /// <summary></summary>
    CRSel = 0xF7,
    /// <summary></summary>
    EXSel = 0xF8,
    /// <summary></summary>
    EREOF = 0xF9,
    /// <summary></summary>
    Play = 0xFA,
    /// <summary></summary>
    Zoom = 0xFB,
    /// <summary></summary>
    Noname = 0xFC,
    /// <summary></summary>
    PA1 = 0xFD,
    /// <summary></summary>
    OEMClear = 0xFE,
};

// regex to generate this map from the enum:
// https://regex101.com/r/uoX4Mz/1
// "(?! )(.*?)(?= = .*)" (regex)
// "\t{KeyCode::$1, static_cast<USHORT>(KeyCode::$1)},\n" (list function)
// THIS EXISTS ONLY FOR RUNTIME OPTIMIZATION
static map<KeyCode, USHORT> KeyCodes = {
	{KeyCode::Mouse0, static_cast<USHORT>(KeyCode::Mouse0)},
    {KeyCode::Mouse1, static_cast<USHORT>(KeyCode::Mouse1)},
    {KeyCode::Cancel, static_cast<USHORT>(KeyCode::Cancel)},
    {KeyCode::Mouse2, static_cast<USHORT>(KeyCode::Mouse2)},
    {KeyCode::ExtraButton1, static_cast<USHORT>(KeyCode::ExtraButton1)},
    {KeyCode::ExtraButton2, static_cast<USHORT>(KeyCode::ExtraButton2)},
    {KeyCode::Back, static_cast<USHORT>(KeyCode::Back)},
    {KeyCode::Tab, static_cast<USHORT>(KeyCode::Tab)},
    {KeyCode::Clear, static_cast<USHORT>(KeyCode::Clear)},
    {KeyCode::Return, static_cast<USHORT>(KeyCode::Return)},
    {KeyCode::Shift, static_cast<USHORT>(KeyCode::Shift)},
    {KeyCode::Control, static_cast<USHORT>(KeyCode::Control)},
    {KeyCode::Menu, static_cast<USHORT>(KeyCode::Menu)},
    {KeyCode::Pause, static_cast<USHORT>(KeyCode::Pause)},
    {KeyCode::CapsLock, static_cast<USHORT>(KeyCode::CapsLock)},
    {KeyCode::Kana, static_cast<USHORT>(KeyCode::Kana)},
    {KeyCode::Hangeul, static_cast<USHORT>(KeyCode::Hangeul)},
    {KeyCode::Hangul, static_cast<USHORT>(KeyCode::Hangul)},
    {KeyCode::Junja, static_cast<USHORT>(KeyCode::Junja)},
    {KeyCode::Final, static_cast<USHORT>(KeyCode::Final)},
    {KeyCode::Hanja, static_cast<USHORT>(KeyCode::Hanja)},
    {KeyCode::Kanji, static_cast<USHORT>(KeyCode::Kanji)},
    {KeyCode::Escape, static_cast<USHORT>(KeyCode::Escape)},
    {KeyCode::Convert, static_cast<USHORT>(KeyCode::Convert)},
    {KeyCode::NonConvert, static_cast<USHORT>(KeyCode::NonConvert)},
    {KeyCode::Accept, static_cast<USHORT>(KeyCode::Accept)},
    {KeyCode::ModeChange, static_cast<USHORT>(KeyCode::ModeChange)},
    {KeyCode::Space, static_cast<USHORT>(KeyCode::Space)},
    {KeyCode::Prior, static_cast<USHORT>(KeyCode::Prior)},
    {KeyCode::Next, static_cast<USHORT>(KeyCode::Next)},
    {KeyCode::End, static_cast<USHORT>(KeyCode::End)},
    {KeyCode::Home, static_cast<USHORT>(KeyCode::Home)},
    {KeyCode::Left, static_cast<USHORT>(KeyCode::Left)},
    {KeyCode::Up, static_cast<USHORT>(KeyCode::Up)},
    {KeyCode::Right, static_cast<USHORT>(KeyCode::Right)},
    {KeyCode::Down, static_cast<USHORT>(KeyCode::Down)},
    {KeyCode::Select, static_cast<USHORT>(KeyCode::Select)},
    {KeyCode::Print, static_cast<USHORT>(KeyCode::Print)},
    {KeyCode::Execute, static_cast<USHORT>(KeyCode::Execute)},
    {KeyCode::Snapshot, static_cast<USHORT>(KeyCode::Snapshot)},
    {KeyCode::Insert, static_cast<USHORT>(KeyCode::Insert)},
    {KeyCode::Delete, static_cast<USHORT>(KeyCode::Delete)},
    {KeyCode::Help, static_cast<USHORT>(KeyCode::Help)},
    {KeyCode::Alpha0, static_cast<USHORT>(KeyCode::Alpha0)},
    {KeyCode::Alpha1, static_cast<USHORT>(KeyCode::Alpha1)},
    {KeyCode::Alpha2, static_cast<USHORT>(KeyCode::Alpha2)},
    {KeyCode::Alpha3, static_cast<USHORT>(KeyCode::Alpha3)},
    {KeyCode::Alpha4, static_cast<USHORT>(KeyCode::Alpha4)},
    {KeyCode::Alpha5, static_cast<USHORT>(KeyCode::Alpha5)},
    {KeyCode::Alpha6, static_cast<USHORT>(KeyCode::Alpha6)},
    {KeyCode::Alpha7, static_cast<USHORT>(KeyCode::Alpha7)},
    {KeyCode::Alpha8, static_cast<USHORT>(KeyCode::Alpha8)},
    {KeyCode::Alpha9, static_cast<USHORT>(KeyCode::Alpha9)},
    {KeyCode::A, static_cast<USHORT>(KeyCode::A)},
    {KeyCode::B, static_cast<USHORT>(KeyCode::B)},
    {KeyCode::C, static_cast<USHORT>(KeyCode::C)},
    {KeyCode::D, static_cast<USHORT>(KeyCode::D)},
    {KeyCode::E, static_cast<USHORT>(KeyCode::E)},
    {KeyCode::F, static_cast<USHORT>(KeyCode::F)},
    {KeyCode::G, static_cast<USHORT>(KeyCode::G)},
    {KeyCode::H, static_cast<USHORT>(KeyCode::H)},
    {KeyCode::I, static_cast<USHORT>(KeyCode::I)},
    {KeyCode::J, static_cast<USHORT>(KeyCode::J)},
    {KeyCode::K, static_cast<USHORT>(KeyCode::K)},
    {KeyCode::L, static_cast<USHORT>(KeyCode::L)},
    {KeyCode::M, static_cast<USHORT>(KeyCode::M)},
    {KeyCode::N, static_cast<USHORT>(KeyCode::N)},
    {KeyCode::O, static_cast<USHORT>(KeyCode::O)},
    {KeyCode::P, static_cast<USHORT>(KeyCode::P)},
    {KeyCode::Q, static_cast<USHORT>(KeyCode::Q)},
    {KeyCode::R, static_cast<USHORT>(KeyCode::R)},
    {KeyCode::S, static_cast<USHORT>(KeyCode::S)},
    {KeyCode::T, static_cast<USHORT>(KeyCode::T)},
    {KeyCode::U, static_cast<USHORT>(KeyCode::U)},
    {KeyCode::V, static_cast<USHORT>(KeyCode::V)},
    {KeyCode::W, static_cast<USHORT>(KeyCode::W)},
    {KeyCode::X, static_cast<USHORT>(KeyCode::X)},
    {KeyCode::Y, static_cast<USHORT>(KeyCode::Y)},
    {KeyCode::Z, static_cast<USHORT>(KeyCode::Z)},
    {KeyCode::LeftWindows, static_cast<USHORT>(KeyCode::LeftWindows)},
    {KeyCode::RightWindows, static_cast<USHORT>(KeyCode::RightWindows)},
    {KeyCode::Application, static_cast<USHORT>(KeyCode::Application)},
    {KeyCode::Sleep, static_cast<USHORT>(KeyCode::Sleep)},
    {KeyCode::Keypad0, static_cast<USHORT>(KeyCode::Keypad0)},
    {KeyCode::Keypad1, static_cast<USHORT>(KeyCode::Keypad1)},
    {KeyCode::Keypad2, static_cast<USHORT>(KeyCode::Keypad2)},
    {KeyCode::Keypad3, static_cast<USHORT>(KeyCode::Keypad3)},
    {KeyCode::Keypad4, static_cast<USHORT>(KeyCode::Keypad4)},
    {KeyCode::Keypad5, static_cast<USHORT>(KeyCode::Keypad5)},
    {KeyCode::Keypad6, static_cast<USHORT>(KeyCode::Keypad6)},
    {KeyCode::Keypad7, static_cast<USHORT>(KeyCode::Keypad7)},
    {KeyCode::Keypad8, static_cast<USHORT>(KeyCode::Keypad8)},
    {KeyCode::Keypad9, static_cast<USHORT>(KeyCode::Keypad9)},
    {KeyCode::KeypadMultiply, static_cast<USHORT>(KeyCode::KeypadMultiply)},
    {KeyCode::KeypadPlus, static_cast<USHORT>(KeyCode::KeypadPlus)},
    {KeyCode::Separator, static_cast<USHORT>(KeyCode::Separator)},
    {KeyCode::KeypadMinus, static_cast<USHORT>(KeyCode::KeypadMinus)},
    {KeyCode::KeypadPeriod, static_cast<USHORT>(KeyCode::KeypadPeriod)},
    {KeyCode::KeypadDivide, static_cast<USHORT>(KeyCode::KeypadDivide)},
    {KeyCode::F1, static_cast<USHORT>(KeyCode::F1)},
    {KeyCode::F2, static_cast<USHORT>(KeyCode::F2)},
    {KeyCode::F3, static_cast<USHORT>(KeyCode::F3)},
    {KeyCode::F4, static_cast<USHORT>(KeyCode::F4)},
    {KeyCode::F5, static_cast<USHORT>(KeyCode::F5)},
    {KeyCode::F6, static_cast<USHORT>(KeyCode::F6)},
    {KeyCode::F7, static_cast<USHORT>(KeyCode::F7)},
    {KeyCode::F8, static_cast<USHORT>(KeyCode::F8)},
    {KeyCode::F9, static_cast<USHORT>(KeyCode::F9)},
    {KeyCode::F10, static_cast<USHORT>(KeyCode::F10)},
    {KeyCode::F11, static_cast<USHORT>(KeyCode::F11)},
    {KeyCode::F12, static_cast<USHORT>(KeyCode::F12)},
    {KeyCode::F13, static_cast<USHORT>(KeyCode::F13)},
    {KeyCode::F14, static_cast<USHORT>(KeyCode::F14)},
    {KeyCode::F15, static_cast<USHORT>(KeyCode::F15)},
    {KeyCode::F16, static_cast<USHORT>(KeyCode::F16)},
    {KeyCode::F17, static_cast<USHORT>(KeyCode::F17)},
    {KeyCode::F18, static_cast<USHORT>(KeyCode::F18)},
    {KeyCode::F19, static_cast<USHORT>(KeyCode::F19)},
    {KeyCode::F20, static_cast<USHORT>(KeyCode::F20)},
    {KeyCode::F21, static_cast<USHORT>(KeyCode::F21)},
    {KeyCode::F22, static_cast<USHORT>(KeyCode::F22)},
    {KeyCode::F23, static_cast<USHORT>(KeyCode::F23)},
    {KeyCode::F24, static_cast<USHORT>(KeyCode::F24)},
    {KeyCode::NumLock, static_cast<USHORT>(KeyCode::NumLock)},
    {KeyCode::ScrollLock, static_cast<USHORT>(KeyCode::ScrollLock)},
    {KeyCode::NEC_Equal, static_cast<USHORT>(KeyCode::NEC_Equal)},
    {KeyCode::Fujitsu_Jisho, static_cast<USHORT>(KeyCode::Fujitsu_Jisho)},
    {KeyCode::Fujitsu_Masshou, static_cast<USHORT>(KeyCode::Fujitsu_Masshou)},
    {KeyCode::Fujitsu_Touroku, static_cast<USHORT>(KeyCode::Fujitsu_Touroku)},
    {KeyCode::Fujitsu_Loya, static_cast<USHORT>(KeyCode::Fujitsu_Loya)},
    {KeyCode::Fujitsu_Roya, static_cast<USHORT>(KeyCode::Fujitsu_Roya)},
    {KeyCode::LeftShift, static_cast<USHORT>(KeyCode::LeftShift)},
    {KeyCode::RightShift, static_cast<USHORT>(KeyCode::RightShift)},
    {KeyCode::LeftControl, static_cast<USHORT>(KeyCode::LeftControl)},
    {KeyCode::RightControl, static_cast<USHORT>(KeyCode::RightControl)},
    {KeyCode::LeftMenu, static_cast<USHORT>(KeyCode::LeftMenu)},
    {KeyCode::RightMenu, static_cast<USHORT>(KeyCode::RightMenu)},
    {KeyCode::BrowserBack, static_cast<USHORT>(KeyCode::BrowserBack)},
    {KeyCode::BrowserForward, static_cast<USHORT>(KeyCode::BrowserForward)},
    {KeyCode::BrowserRefresh, static_cast<USHORT>(KeyCode::BrowserRefresh)},
    {KeyCode::BrowserStop, static_cast<USHORT>(KeyCode::BrowserStop)},
    {KeyCode::BrowserSearch, static_cast<USHORT>(KeyCode::BrowserSearch)},
    {KeyCode::BrowserFavorites, static_cast<USHORT>(KeyCode::BrowserFavorites)},
    {KeyCode::BrowserHome, static_cast<USHORT>(KeyCode::BrowserHome)},
    {KeyCode::VolumeMute, static_cast<USHORT>(KeyCode::VolumeMute)},
    {KeyCode::VolumeDown, static_cast<USHORT>(KeyCode::VolumeDown)},
    {KeyCode::VolumeUp, static_cast<USHORT>(KeyCode::VolumeUp)},
    {KeyCode::MediaNextTrack, static_cast<USHORT>(KeyCode::MediaNextTrack)},
    {KeyCode::MediaPrevTrack, static_cast<USHORT>(KeyCode::MediaPrevTrack)},
    {KeyCode::MediaStop, static_cast<USHORT>(KeyCode::MediaStop)},
    {KeyCode::MediaPlayPause, static_cast<USHORT>(KeyCode::MediaPlayPause)},
    {KeyCode::LaunchMail, static_cast<USHORT>(KeyCode::LaunchMail)},
    {KeyCode::LaunchMediaSelect, static_cast<USHORT>(KeyCode::LaunchMediaSelect)},
    {KeyCode::LaunchApplication1, static_cast<USHORT>(KeyCode::LaunchApplication1)},
    {KeyCode::LaunchApplication2, static_cast<USHORT>(KeyCode::LaunchApplication2)},
    {KeyCode::OEM1, static_cast<USHORT>(KeyCode::OEM1)},
    {KeyCode::OEMPlus, static_cast<USHORT>(KeyCode::OEMPlus)},
    {KeyCode::OEMComma, static_cast<USHORT>(KeyCode::OEMComma)},
    {KeyCode::OEMMinus, static_cast<USHORT>(KeyCode::OEMMinus)},
    {KeyCode::OEMPeriod, static_cast<USHORT>(KeyCode::OEMPeriod)},
    {KeyCode::OEM2, static_cast<USHORT>(KeyCode::OEM2)},
    {KeyCode::OEM3, static_cast<USHORT>(KeyCode::OEM3)},
    {KeyCode::OEM4, static_cast<USHORT>(KeyCode::OEM4)},
    {KeyCode::OEM5, static_cast<USHORT>(KeyCode::OEM5)},
    {KeyCode::OEM6, static_cast<USHORT>(KeyCode::OEM6)},
    {KeyCode::OEM7, static_cast<USHORT>(KeyCode::OEM7)},
    {KeyCode::OEM8, static_cast<USHORT>(KeyCode::OEM8)},
    {KeyCode::OEMAX, static_cast<USHORT>(KeyCode::OEMAX)},
    {KeyCode::OEM102, static_cast<USHORT>(KeyCode::OEM102)},
    {KeyCode::ICOHelp, static_cast<USHORT>(KeyCode::ICOHelp)},
    {KeyCode::ICO00, static_cast<USHORT>(KeyCode::ICO00)},
    {KeyCode::ProcessKey, static_cast<USHORT>(KeyCode::ProcessKey)},
    {KeyCode::ICOClear, static_cast<USHORT>(KeyCode::ICOClear)},
    {KeyCode::Packet, static_cast<USHORT>(KeyCode::Packet)},
    {KeyCode::OEMReset, static_cast<USHORT>(KeyCode::OEMReset)},
    {KeyCode::OEMJump, static_cast<USHORT>(KeyCode::OEMJump)},
    {KeyCode::OEMPA1, static_cast<USHORT>(KeyCode::OEMPA1)},
    {KeyCode::OEMPA2, static_cast<USHORT>(KeyCode::OEMPA2)},
    {KeyCode::OEMPA3, static_cast<USHORT>(KeyCode::OEMPA3)},
    {KeyCode::OEMWSCtrl, static_cast<USHORT>(KeyCode::OEMWSCtrl)},
    {KeyCode::OEMCUSel, static_cast<USHORT>(KeyCode::OEMCUSel)},
    {KeyCode::OEMATTN, static_cast<USHORT>(KeyCode::OEMATTN)},
    {KeyCode::OEMFinish, static_cast<USHORT>(KeyCode::OEMFinish)},
    {KeyCode::OEMCopy, static_cast<USHORT>(KeyCode::OEMCopy)},
    {KeyCode::OEMAuto, static_cast<USHORT>(KeyCode::OEMAuto)},
    {KeyCode::OEMENLW, static_cast<USHORT>(KeyCode::OEMENLW)},
    {KeyCode::OEMBackTab, static_cast<USHORT>(KeyCode::OEMBackTab)},
    {KeyCode::ATTN, static_cast<USHORT>(KeyCode::ATTN)},
    {KeyCode::CRSel, static_cast<USHORT>(KeyCode::CRSel)},
    {KeyCode::EXSel, static_cast<USHORT>(KeyCode::EXSel)},
    {KeyCode::EREOF, static_cast<USHORT>(KeyCode::EREOF)},
    {KeyCode::Play, static_cast<USHORT>(KeyCode::Play)},
    {KeyCode::Zoom, static_cast<USHORT>(KeyCode::Zoom)},
    {KeyCode::Noname, static_cast<USHORT>(KeyCode::Noname)},
    {KeyCode::PA1, static_cast<USHORT>(KeyCode::PA1)},
    {KeyCode::OEMClear, static_cast<USHORT>(KeyCode::OEMClear)},
};
