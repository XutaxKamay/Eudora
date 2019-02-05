#include "Includes.hxx"
#include "Lib.hxx"

// Entry point of the dll : https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms682596(v=vs.85).aspx

/*
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnHello( wxCommandEvent& event );
    void OnExit( wxCommandEvent& event );
    void OnAbout( wxCommandEvent& event );
};
enum
{
    ID_Hello = 1
};
wxIMPLEMENT_APP_NO_MAIN( MyApp );
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show( true );
    return true;
}
MyFrame::MyFrame()
    : wxFrame( NULL , wxID_ANY , "Hello World" )
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append( ID_Hello , "&Hello...\tCtrl-H" ,
                      "Help string shown in status bar for this menu item" );
    menuFile->AppendSeparator();
    menuFile->Append( wxID_EXIT );
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append( wxID_ABOUT );
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile , "&File" );
    menuBar->Append( menuHelp , "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
    Bind( wxEVT_MENU , &MyFrame::OnHello , this , ID_Hello );
    Bind( wxEVT_MENU , &MyFrame::OnAbout , this , wxID_ABOUT );
    Bind( wxEVT_MENU , &MyFrame::OnExit , this , wxID_EXIT );
}
void MyFrame::OnExit( wxCommandEvent& event )
{
    Close( true );
}
void MyFrame::OnAbout( wxCommandEvent& event )
{
    wxMessageBox( "This is a wxWidgets Hello World example" ,
                  "About Hello World" , wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello( wxCommandEvent& event )
{
    wxLogMessage( "Hello world from wxWidgets!" );
}*/

__declspec( thread ) int tls_i = 133464527;

DWORD __stdcall Routine( Pointer pThing )
{
    // If the dll is attached to the process we can start doing things.
    // We must create a thread inside the dll because the loader of the dll would be stuck in some cases, it would be waiting for the thread finishing so we avoid that.

    AllocConsole();

    String buf[ 0xFF ];
    wsprintf( buf , TEXT( "%i 0x%p 0x%p" ) , tls_i , &tls_i , pThing );
    MessageBox( 0 , buf , 0 , MB_OK );

   // CreateThread( 0 , 0 , ( LPTHREAD_START_ROUTINE ) Routine , pThing , 0 , 0 );

    return 1;
}

uHEX32 WINAPI DllMain(
    Pointer pModule ,  // Address of the current module
    HEX HexReason ,     // Obvious
    Pointer pReserved )  // Something that is useless. Wich we can use for a manual mapper for example.
{
    DisableThreadLibraryCalls( ( HMODULE ) pModule );

    if ( HexReason == DLL_PROCESS_ATTACH )
    {

        Routine( pModule );

        tls_i = 3;

        CreateThread( 0 , 0 , ( LPTHREAD_START_ROUTINE ) Routine , pModule , 0 , 0 );

        //WaitForSingleObject( pThread , INFINITE );
    }

    return 1;
}