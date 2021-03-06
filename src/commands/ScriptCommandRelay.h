/**********************************************************************

   Audacity - A Digital Audio Editor
   Copyright 1999-2018 Audacity Team
   File License: wxWidgets

   Dan Horgan

******************************************************************//**

\file ScriptCommandRelay.h
\brief Contains declarations for ScriptCommandRelay

*//*******************************************************************/

#ifndef __SCRIPT_COMMAND_RELAY__
#define __SCRIPT_COMMAND_RELAY__

#include "../Audacity.h"

#include "../MemoryX.h"

class CommandHandler;
class ResponseQueue;
class Response;
class ResponseQueueTarget;
class AudacityProject;
class OldStyleCommand;
using OldStyleCommandPointer = std::shared_ptr<OldStyleCommand>;
class wxString;

typedef int (*tpExecScriptServerFunc)( wxString * pIn, wxString * pOut);
typedef int (*tpRegScriptServerFunc)(tpExecScriptServerFunc pFn);

extern "C" {
      AUDACITY_DLL_API int ExecCommand(wxString *pIn, wxString *pOut);
} // End 'extern C'

class ScriptCommandRelay
{
   private:
      // N.B. Static class members also have to be declared in the .cpp file
      static CommandHandler *sCmdHandler;
      static tpRegScriptServerFunc sScriptFn;
      static ResponseQueue sResponseQueue;

   public:

      static void SetRegScriptServerFunc(tpRegScriptServerFunc scriptFn);
      static void SetCommandHandler(CommandHandler &ch);

      static void Run();
      static void PostCommand(AudacityProject *project, const OldStyleCommandPointer &cmd);
      static void SendResponse(const wxString &response);
      static Response ReceiveResponse();
      static std::shared_ptr<ResponseQueueTarget> GetResponseTarget();
};

#endif /* End of include guard: __SCRIPT_COMMAND_RELAY__ */
