// Copyright 2009 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <string>
#include <utility>

#include <fmt/format.h>

namespace Common
{
// Message alerts
enum class MsgType
{
  Information,
  Question,
  Warning,
  Critical
};

using MsgAlertHandler = bool (*)(const char* caption, const char* text, bool yes_no, MsgType style);
using StringTranslator = std::string (*)(const char* text);

void RegisterMsgAlertHandler(MsgAlertHandler handler);
void RegisterStringTranslator(StringTranslator translator);

std::string GetStringT(const char* string);
bool MsgAlert(bool yes_no, MsgType style, const char* format, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 3, 4)))
#endif
    ;
void SetEnableAlert(bool enable);

// Like fmt::format, except the string becomes translatable
template <typename... Args>
std::string FmtFormatT(const char* string, Args&&... args)
{
  return fmt::format(Common::GetStringT(string), std::forward<Args>(args)...);
}
}  // namespace Common

#define SuccessAlert(format, ...)                                                                  \
  Common::MsgAlert(false, Common::MsgType::Information, format, ##__VA_ARGS__)

#define PanicAlert(format, ...)                                                                    \
  Common::MsgAlert(false, Common::MsgType::Warning, format, ##__VA_ARGS__)

#define PanicYesNo(format, ...)                                                                    \
  Common::MsgAlert(true, Common::MsgType::Warning, format, ##__VA_ARGS__)

#define AskYesNo(format, ...)                                                                      \
  Common::MsgAlert(true, Common::MsgType::Question, format, ##__VA_ARGS__)

#define CriticalAlert(format, ...)                                                                 \
  Common::MsgAlert(false, Common::MsgType::Critical, format, ##__VA_ARGS__)

// Use these macros (that do the same thing) if the message should be translated.
#define SuccessAlertT(format, ...)                                                                 \
  Common::MsgAlert(false, Common::MsgType::Information, format, ##__VA_ARGS__)

#define PanicAlertT(format, ...)                                                                   \
  Common::MsgAlert(false, Common::MsgType::Warning, format, ##__VA_ARGS__)

#define PanicYesNoT(format, ...)                                                                   \
  Common::MsgAlert(true, Common::MsgType::Warning, format, ##__VA_ARGS__)

#define AskYesNoT(format, ...)                                                                     \
  Common::MsgAlert(true, Common::MsgType::Question, format, ##__VA_ARGS__)

#define CriticalAlertT(format, ...)                                                                \
  Common::MsgAlert(false, Common::MsgType::Critical, format, ##__VA_ARGS__)
