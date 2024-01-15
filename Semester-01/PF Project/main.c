#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/*function declarations for file processing*/
void recordAdd(char* domain,char* username,char* password);
void recordUpdate(char* domain,char* username,char* password);
void recordDelete(char* domain,char* username);
void recordRead(void);
char* recordSearch(const char* domain, const char* username);

/*function declarations for verification system*/
void VerificationSystem(void);
void ContinueButton(GtkButton* button,gpointer data);
bool verification(char* email, char* password);

/*function declarations for listing passwords*/
void PasswordsViewingModule(void);
void reloadcontent(GtkWidget* button,gpointer data);

/*function declarations for adding passwords*/
void PasswordsAddingModule(void);
void ShowDomainEntry(GtkWidget *Choice);
void PassAdd(GtkButton *button);

/*function declarations for deleting passwords*/
void PasswordDeletingModule(void);
void PassDelete(GtkButton *button,gpointer user);
void PassSearch(GtkButton *button,gpointer user);

/*function declarations for updating passwords*/
void PasswordUpdatingModule(void);
void PassUpdate(GtkButton *button);

/*searching and error handling function declarations*/
bool domainVerify(char* domain);
bool usernameVerify(char* username);
void errorRNF(void);
void errorFTOF(void);
void errorFTCF(void);
void errorIDE(void);

/*some other functions*/
void ShowPassword(GtkWidget *password,gpointer data);
void SettingWindowSize(GtkNotebook *notebook,GtkWidget *page,guint page_num,gpointer user_data);
gboolean PassWordHealth(GtkWidget* widget, GdkEventKey* event,gpointer user_data);

/*Encryption and Decryption*/
void encryption(char* key);
void decryption(char* key);

/*Record structure*/
typedef struct{
    char* domain;
    char* username;
    char* password;
} User;


/*Main widgets declarations*/
GtkWidget* ChamberOfSecrets; //Main window
GtkWidget* PrimaryNotebook; //tabs switching

/*Widgets declarations for listing passwords*/
GtkWidget* listmain; //main box for listing password
GtkWidget* headingforlist; //header box
GtkWidget* domain; //header label
GtkWidget* username; //header label
GtkWidget* password; //header label
GtkWidget* scrollingWindow; //scrolling window (for list items)
GtkWidget* list; //list box
GtkWidget* reload;

/*Widgets declaration for Adding a new password*/
GtkWidget* AddBox; //main box for this module
GtkWidget* ButtonBox1;
GtkWidget* LabelBox1;
GtkWidget* EntryBox1; 
GtkWidget* ELcombined1;
GtkWidget* DomainChoice;
GtkWidget* DomainEnter;
GtkWidget* UserEnter;
GtkWidget* PassBox1;
GtkWidget* PassEnter;
GtkWidget* PassHealth1;
GtkWidget* ChooseDomain;
GtkWidget* EnterDomain;
GtkWidget* EnterUser;
GtkWidget* EnterPass;
GtkWidget* AddPlease;

/*Widgets declaration for Deleting existing Password*/
GtkWidget* DeleteBox; //main box for this module
GtkWidget* ButtonBox21;
GtkWidget* ButtonBox22;
GtkWidget* LabelBox2;
GtkWidget* EntryBox2;
GtkWidget* ELcombined2; 
GtkWidget* AddressDelete;
GtkWidget* PasswordDelete;
GtkWidget* DeleteAddress;
GtkWidget* DeletePassword;
GtkWidget* DeletePlease;
GtkWidget* DeleteSearch;

/*Widgets declaration for Updating Password*/
GtkWidget* UpdateBox; //main box for this module
GtkWidget* ButtonBox31;
GtkWidget* LabelBox3;
GtkWidget* EntryBox3;
GtkWidget* ELcombined3; 
GtkWidget* AddressUpdate;
GtkWidget* PassBox2;
GtkWidget* PasswordUpdate;
GtkWidget* PassHealth2;
GtkWidget* UpdateAddress;
GtkWidget* UpdatePassword;
GtkWidget* UpdatePlease;

/*Verification system*/
GtkWidget* verifyWindow;
GtkWidget* MainBox;
GtkWidget* ButtonsBox;
GtkWidget* Note;
GtkWidget* EmailEnter;
GtkWidget* PasswordEnter;
GtkWidget* TwoFAEnter;
GtkWidget* Continue;
GtkWidget* Enter;

int main(int argc, char *argv[]){
    gtk_init(&argc,&argv);

    //Main window
    ChamberOfSecrets = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(ChamberOfSecrets),"Chamber of Secrets");
    gtk_window_set_default_size(GTK_WINDOW(ChamberOfSecrets),520,520);
    gtk_window_set_position(GTK_WINDOW(ChamberOfSecrets),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(ChamberOfSecrets),TRUE);
    g_signal_connect(ChamberOfSecrets,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    
    PrimaryNotebook = gtk_notebook_new(); 
    g_signal_connect(PrimaryNotebook,"switch-page",G_CALLBACK(SettingWindowSize),NULL);
    gtk_container_add(GTK_CONTAINER(ChamberOfSecrets), PrimaryNotebook);

    PasswordsViewingModule();
    PasswordsAddingModule();
    PasswordDeletingModule();
    PasswordUpdatingModule();

    gtk_notebook_append_page(GTK_NOTEBOOK(PrimaryNotebook),listmain,gtk_label_new("View Passwords"));
    gtk_notebook_append_page(GTK_NOTEBOOK(PrimaryNotebook),AddBox,gtk_label_new("Add Passwords"));
    gtk_notebook_append_page(GTK_NOTEBOOK(PrimaryNotebook),DeleteBox,gtk_label_new("Delete Passwords"));
    gtk_notebook_append_page(GTK_NOTEBOOK(PrimaryNotebook),UpdateBox,gtk_label_new("Update Password"));

    VerificationSystem();

    gtk_main();
    return 0;
}

/*function declarations for verification system*/
void VerificationSystem(void){
    //creating window and customizing it
    verifyWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(verifyWindow),"User Verification");
    gtk_window_set_default_size(GTK_WINDOW(verifyWindow),520,-1);
    gtk_window_set_position(GTK_WINDOW(verifyWindow),GTK_WIN_POS_CENTER);
    g_signal_connect(verifyWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    //declaring box
    MainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);

    //initializing widgets
    Note = gtk_label_new("Please provide the correct details to continue");
    EmailEnter = gtk_entry_new();
    PasswordEnter = gtk_entry_new();
    TwoFAEnter = gtk_entry_new();
    Continue = gtk_button_new_with_label("Continue");
    Enter = gtk_button_new_with_label("Enter");

    //customizing entries
    gtk_entry_set_placeholder_text(GTK_ENTRY(EmailEnter),"Enter admin email");
    gtk_entry_set_placeholder_text(GTK_ENTRY(PasswordEnter),"Enter admin password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(TwoFAEnter),"Enter verification code");
    gtk_entry_set_visibility(GTK_ENTRY(PasswordEnter),FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(PasswordEnter), (gunichar)0x25CF); //setting dot as invisible character]
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(PasswordEnter), GTK_ENTRY_ICON_SECONDARY, "view-reveal-symbolic.symbolic"); //eye icon
    gtk_entry_set_icon_activatable(GTK_ENTRY(PasswordEnter),GTK_ENTRY_ICON_SECONDARY, TRUE); //eye icon can be clicked
    g_signal_connect(PasswordEnter,"icon-press",G_CALLBACK(ShowPassword),NULL);
    g_signal_connect(Continue,"clicked",G_CALLBACK(ContinueButton),NULL);


    gtk_box_pack_start(GTK_BOX(MainBox),Note,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(MainBox),EmailEnter,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(MainBox),PasswordEnter,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(MainBox),TwoFAEnter,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(MainBox),Continue,TRUE,TRUE,0);

    gtk_container_add(GTK_CONTAINER(verifyWindow),MainBox);

    gtk_widget_show_all(verifyWindow);

    gtk_widget_hide(GTK_WIDGET(TwoFAEnter)); //hiding verification code entry

}

void ContinueButton(GtkButton* button,gpointer data){
    char* emailHeYe = (char*)gtk_entry_get_text(GTK_ENTRY(EmailEnter));
    char* passwordHeYe = (char*)gtk_entry_get_text(GTK_ENTRY(PasswordEnter));
    if(!verification(emailHeYe,passwordHeYe)){
        GtkWidget *error;
        error = gtk_message_dialog_new(GTK_WINDOW(verifyWindow),GTK_DIALOG_MODAL,
    GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Error: 001\nIncorrect Credentials\n");
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
        return;
    }
    if(!gtk_widget_get_visible(TwoFAEnter)){
        gtk_widget_show(TwoFAEnter);
        return;
    }
    char* twofaHun = (char*)gtk_entry_get_text(GTK_ENTRY(TwoFAEnter));
    if(strcmp(twofaHun,"112233")){
        GtkWidget *error;
        error = gtk_message_dialog_new(GTK_WINDOW(verifyWindow),GTK_DIALOG_MODAL,
    GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Error: 002\nVerification code is incorrect\n");
        gtk_dialog_run(GTK_DIALOG(error));
        gtk_widget_destroy(error);
        return;
    }
    // gtk_widget_destroy(GTK_WIDGET(verifyWindow));
    gtk_widget_hide(verifyWindow);
    gtk_widget_show_all(ChamberOfSecrets);
    gtk_widget_hide(GTK_WIDGET(DomainEnter));
    gtk_widget_hide(GTK_WIDGET(EnterDomain));
}

//function definitions for listing passwords
void PasswordsViewingModule(void){

    //initializing widgets
    listmain = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    headingforlist = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    domain = gtk_label_new("Domain");
    username = gtk_label_new("Username");
    password = gtk_label_new("Password");
    scrollingWindow = gtk_scrolled_window_new(NULL,NULL);
    list = gtk_list_box_new();
    reload = gtk_button_new_with_label("Reload Content");
    g_signal_connect(reload,"clicked",G_CALLBACK(reloadcontent),NULL);

    //displaying text
    recordRead();
    //widgets in the boxes
    gtk_container_add(GTK_CONTAINER(scrollingWindow),list); //adding list box to the scrolling window
    gtk_box_pack_start(GTK_BOX(headingforlist),domain,TRUE,TRUE,0); //putting labels in the header box
    gtk_box_pack_start(GTK_BOX(headingforlist),username,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(headingforlist),password,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(listmain),headingforlist,FALSE,TRUE,0); //putting header in list main box
    gtk_box_pack_start(GTK_BOX(listmain),scrollingWindow,TRUE,TRUE,0); //scrolling window in list main box
    gtk_box_pack_start(GTK_BOX(listmain),reload,FALSE,TRUE,0); 
}

void reloadcontent(GtkWidget* button,gpointer data){
    gtk_container_foreach(GTK_CONTAINER(list), (GtkCallback)gtk_widget_destroy, NULL);
    recordRead();
}

//function definitions for adding passwords
void PasswordsAddingModule(void){
    //initializing boxes
    AddBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    ButtonBox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    EntryBox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    LabelBox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    ELcombined1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    PassBox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //initializing combo and entries
    DomainChoice = gtk_combo_box_text_new();
    DomainEnter = gtk_entry_new();
    UserEnter = gtk_entry_new();
    PassEnter = gtk_entry_new();
    PassHealth1 = gtk_entry_new();
    //initializing labels
    ChooseDomain = gtk_label_new("Choose Your Domain");
    EnterDomain = gtk_label_new("Enter Domain");
    EnterUser = gtk_label_new("Enter Username");
    EnterPass = gtk_label_new("Enter Password");
    //initializing buttons
    AddPlease = gtk_button_new_with_label("Confirm Add");

    //hiding widgets so that we can reveal them when clicked on "others"
    gtk_widget_hide(GTK_WIDGET(DomainEnter));
    gtk_widget_hide(GTK_WIDGET(EnterDomain));
    //setting placeholder text for entries
    gtk_entry_set_placeholder_text(GTK_ENTRY(DomainEnter),"nu.edu.pk");
    gtk_entry_set_placeholder_text(GTK_ENTRY(UserEnter),"k231234");
    gtk_entry_set_placeholder_text(GTK_ENTRY(PassEnter),"Enter Password");
    gtk_entry_set_placeholder_text(GTK_ENTRY(PassHealth1),"Password Health");
    gtk_entry_set_visibility(GTK_ENTRY(PassEnter),FALSE); //initially disabled the visibility 
    gtk_entry_set_invisible_char(GTK_ENTRY(PassEnter), (gunichar)0x25CF); //setting dot as invisible character]
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(PassEnter), GTK_ENTRY_ICON_SECONDARY, "view-reveal-symbolic.symbolic"); //eye icon
    gtk_entry_set_icon_activatable(GTK_ENTRY(PassEnter),GTK_ENTRY_ICON_SECONDARY, TRUE); //eye icon can be clicked
    g_signal_connect(PassEnter,"icon-press",G_CALLBACK(ShowPassword),NULL); //call back function to show and hide password
    gtk_editable_set_editable(GTK_EDITABLE(PassHealth1),FALSE);

    //adding options to combo box
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(DomainChoice), "gmail.com");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(DomainChoice), "outlook.com");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(DomainChoice), "icloud.com");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(DomainChoice), "yahoo.com");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(DomainChoice), "zoho.com");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(DomainChoice), "others");
    gtk_combo_box_set_active(GTK_COMBO_BOX(DomainChoice),0);
    //callback function for combo box
    g_signal_connect(DomainChoice,"changed",G_CALLBACK(ShowDomainEntry),NULL);
    //callback function when the password is entered
    g_signal_connect(PassEnter,"key-press-event",G_CALLBACK(PassWordHealth),PassHealth1);

    //callback function for button
    g_signal_connect(AddPlease,"clicked",G_CALLBACK(PassAdd),NULL);

    //adding elements in their respective boxes
    gtk_box_pack_start(GTK_BOX(PassBox1),PassEnter,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(PassBox1),PassHealth1,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(EntryBox1),DomainChoice,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(EntryBox1),DomainEnter,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(EntryBox1),UserEnter,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(EntryBox1),PassBox1,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(LabelBox1),ChooseDomain,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(LabelBox1),EnterDomain,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(LabelBox1),EnterUser,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(LabelBox1),EnterPass,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(ELcombined1),LabelBox1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ELcombined1),EntryBox1,TRUE,TRUE,0);
    
    gtk_box_pack_start(GTK_BOX(ButtonBox1),ELcombined1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ButtonBox1),AddPlease,FALSE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(AddBox),ButtonBox1,TRUE,TRUE,0);
}

void ShowDomainEntry(GtkWidget *Choice){
    gint isActive;
    isActive = gtk_combo_box_get_active(GTK_COMBO_BOX(Choice));
    if(isActive==5){
        gtk_widget_show(DomainEnter);
        gtk_widget_show(EnterDomain);
    }else{
        gtk_widget_hide(DomainEnter);
        gtk_widget_hide(EnterDomain);
    }
}

void PassAdd(GtkButton *button){
    User user_data;

    gint isActive = gtk_combo_box_get_active(GTK_COMBO_BOX(DomainChoice));

    user_data.username = (char *)gtk_entry_get_text(GTK_ENTRY(UserEnter));
    user_data.password = (char *)gtk_entry_get_text(GTK_ENTRY(PassEnter));

    if(isActive!=5) 
        user_data.domain = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(DomainChoice));
    else 
        user_data.domain = (char *)gtk_entry_get_text(GTK_ENTRY(DomainEnter));

    if(usernameVerify(user_data.username)==false || domainVerify(user_data.domain)==false){
        errorIDE();
        return;
    }
    printf("All ok");

    recordAdd(user_data.domain,user_data.username,user_data.password);

    return;
}

//function definitions for deleting passwords
void PasswordDeletingModule(void){
    //initializing container boxes
    DeleteBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    ButtonBox21 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    ButtonBox22 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    LabelBox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    EntryBox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    ELcombined2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //initializing search entry and simple entries
    AddressDelete = gtk_search_entry_new();
    PasswordDelete = gtk_entry_new();
    //initializing labels
    DeleteAddress = gtk_label_new("Address to delete");
    DeletePassword = gtk_label_new("Password to delete");
    //initializing button
    DeletePlease = gtk_button_new_with_label("Confirm Delete");
    DeleteSearch = gtk_button_new_with_label("Search for Password");

    g_signal_connect(DeletePlease,"clicked",G_CALLBACK(PassDelete),NULL);
    g_signal_connect(DeleteSearch,"clicked",G_CALLBACK(PassSearch),NULL);

    //some customizations for "PasswordDelete" textbox or entry
    gtk_editable_set_editable(GTK_EDITABLE(PasswordDelete),FALSE); //cannot edit this textbox

    gtk_box_pack_start(GTK_BOX(EntryBox2),AddressDelete,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(EntryBox2),PasswordDelete,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(LabelBox2),DeleteAddress,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(LabelBox2),DeletePassword,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(ELcombined2),LabelBox2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ELcombined2),EntryBox2,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(ButtonBox21),DeleteSearch,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ButtonBox21),DeletePlease,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(ButtonBox22),ELcombined2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ButtonBox22),ButtonBox21,FALSE,TRUE,0);


    gtk_box_pack_start(GTK_BOX(DeleteBox),ButtonBox22,TRUE,TRUE,0);

}

void PassDelete(GtkButton *button,gpointer user){

    User user_data;
    char email[100];
    char* ptr;

    user_data.username = (char *)gtk_entry_get_text(GTK_ENTRY(AddressDelete));

    strcpy(email,user_data.username);
    ptr = strchr(email,'@');

    if(ptr == NULL){  
        errorIDE();
        return;
    }
    
    *ptr = '\0';
    user_data.domain = ptr+1;
    user_data.username = email;
    g_print("Domain: %s\nUsername: %s\nPassword: %s\n",user_data.domain,user_data.username,user_data.password);

    if(usernameVerify(user_data.username)==false || domainVerify(user_data.domain)==false){
        errorIDE();
        return;
    }

    recordDelete(user_data.domain,user_data.username);
    return;
}

void PassSearch(GtkButton *button,gpointer user){
    printf("\nSearching for password");
    const char* domain = (const char*)gtk_entry_get_text(GTK_ENTRY(AddressDelete));
    if(strcmp(domain,"")==0){
        errorIDE();
        return;
    }
    char email[100],* ptr;
    User user_data;

    strcpy(email,domain);
    ptr= strchr(email,'@');
    if(ptr==NULL){
        errorIDE();
        return;
    }
    *ptr = '\0';
    user_data.domain = ptr+1;
    user_data.username = email;
    if(domainVerify(user_data.domain)==false || usernameVerify(user_data.username)==false){
        errorIDE();
        return;
    }
    printf("\nDomain: %s\nUsername: %s",user_data.domain,user_data.username);
    char* pass = recordSearch(user_data.domain,user_data.username);
    if(pass!=NULL){
        printf("\nText was found");
        gtk_entry_set_text(GTK_ENTRY(PasswordDelete),pass);
        free(pass);
    }
    else{
        printf("\nRecord not found");
        gtk_entry_set_text(GTK_ENTRY(PasswordDelete),"Record not found");
    }
    
}

//function definitions for updating passwords
void PasswordUpdatingModule(void){
    //initializing container boxes
    UpdateBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    ButtonBox31 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    LabelBox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    EntryBox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    ELcombined3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    PassBox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //initializing search entry and simple entries
    AddressUpdate = gtk_search_entry_new();
    PasswordUpdate = gtk_entry_new();
    PassHealth2 = gtk_entry_new();
    //initializing labels
    UpdateAddress = gtk_label_new("Enter address to update");
    UpdatePassword = gtk_label_new("Enter new password");
    //initializing button
    UpdatePlease = gtk_button_new_with_label("Confirm Update");
    g_signal_connect(UpdatePlease,"clicked",G_CALLBACK(PassUpdate),NULL);
    g_signal_connect(PasswordUpdate,"key-press-event",G_CALLBACK(PassWordHealth),PassHealth2);

    //some customizations for "PasswordUpdate" entry box
    gtk_entry_set_visibility(GTK_ENTRY(PasswordUpdate),FALSE); //initially disabled the visibility 
    gtk_entry_set_invisible_char(GTK_ENTRY(PasswordUpdate), (gunichar)(0x25CF)); //setting dot as invisible character
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(PasswordUpdate), GTK_ENTRY_ICON_SECONDARY, "view-reveal-symbolic.symbolic"); //eye icon
    gtk_entry_set_icon_activatable(GTK_ENTRY(PasswordUpdate),GTK_ENTRY_ICON_SECONDARY, TRUE); //eye icon can be clicked
    g_signal_connect(PasswordUpdate,"icon-press",G_CALLBACK(ShowPassword),NULL); //call back function to show and hide password
    gtk_editable_set_editable(GTK_EDITABLE(PassHealth2),FALSE);

    gtk_box_pack_start(GTK_BOX(PassBox2),PasswordUpdate,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(PassBox2),PassHealth2,FALSE,FALSE,0);

    gtk_box_pack_start(GTK_BOX(EntryBox3),AddressUpdate,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(EntryBox3),PassBox2,TRUE,TRUE,0);
    
    gtk_box_pack_start(GTK_BOX(LabelBox3),UpdateAddress,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(LabelBox3),UpdatePassword,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(ELcombined3),LabelBox3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ELcombined3),EntryBox3,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(ButtonBox31),ELcombined3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(ButtonBox31),UpdatePlease,FALSE,TRUE,0);
    
    gtk_box_pack_start(GTK_BOX(UpdateBox),ButtonBox31,TRUE,TRUE,0);

}

void PassUpdate(GtkButton *button){
    User user_data;
    char email[100];
    char* ptr;

    user_data.password = (char *)gtk_entry_get_text(GTK_ENTRY(PasswordUpdate));
    user_data.username = (char *)gtk_entry_get_text(GTK_ENTRY(AddressUpdate));

    strcpy(email,user_data.username);
    ptr = strchr(email,'@');

    if(ptr == NULL){  
        errorIDE();
        return;
    }
    
    *ptr = '\0';
    user_data.domain = ptr+1;
    user_data.username = email;
    g_print("Domain: %s\nUsername: %s\nPassword: %s\n",user_data.domain,user_data.username,user_data.password);

    if(usernameVerify(user_data.username)==false || domainVerify(user_data.domain)==false){
        errorIDE();
        return;
    }

    recordUpdate(user_data.domain,user_data.username,user_data.password);
    return;
}

//error handling functions
bool usernameVerify(char* username){
    if(strchr(username,' ')!=NULL){
        return false;
    }
    if(strlen(username)>0){
        for(int i=0;i<strlen(username);i++){
            if((isalnum(username[i]))!=0){
                continue;
            }else if((i!=0 && i!=(strlen(username)-1)) && (username[i]=='.' || username[i]=='-')){
                continue;
            }else{
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}

bool domainVerify(char* domain){
    if(strchr(domain,'.')==NULL){
        return false;
    }
    if(strlen(strrchr(domain,'.'))<2 || (strlen(domain) - strlen(strrchr(domain,'.')))<2){
        return false;
    }
    if(strchr(domain,' ')!=NULL){
        return false;
    }
    for(int i=0;i<strlen(domain);i++){
        if(isalnum(domain[i])!=0){
            continue;
        }else if((i!=0 || i!=strlen(domain)-1) && (domain[i]=='.' || domain[i]=='-')){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

void errorRNF(void){
    GtkWidget *error;
    error = gtk_message_dialog_new(GTK_WINDOW(ChamberOfSecrets),GTK_DIALOG_MODAL,
GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Error: 102\nRecord Not Found!\n");
    gtk_dialog_run(GTK_DIALOG(error));
    gtk_widget_destroy(error);
}

void errorFTOF(void){
    GtkWidget *error;
    error = gtk_message_dialog_new(GTK_WINDOW(ChamberOfSecrets),GTK_DIALOG_MODAL,
GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Error: 503\nFile couldn't open!\n\nHints: \nCheck if you have permission to create or open files in the directory\nCheck if file is created or not... (create if not!!)");
    gtk_dialog_run(GTK_DIALOG(error));
    gtk_widget_destroy(error);
}

void errorFTCF(void){
    GtkWidget *error;
    error = gtk_message_dialog_new(GTK_WINDOW(ChamberOfSecrets),GTK_DIALOG_MODAL,
GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Error: 504\nFile couldn't close!");
    gtk_dialog_run(GTK_DIALOG(error));
    gtk_widget_destroy(error);
}

void errorIDE(void){
    GtkWidget *error;
    error = gtk_message_dialog_new(GTK_WINDOW(ChamberOfSecrets),GTK_DIALOG_MODAL,
GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,"Error: 205\nIncorrect data entry!\n\nHints: \n1. Check if your domain is correct (have extension like .com or .pk)\n2. Make sure that your username is without spaces");
    gtk_dialog_run(GTK_DIALOG(error));
    gtk_widget_destroy(error);
}



//function definitions for file processing
void recordAdd(char* domain,char* username,char* password){
    FILE* file;
    file = fopen("data.txt","a");
    if(file==NULL){
        errorFTOF();
        return;
    }
    encryption(password);
    fprintf(file,"%s %s %s\n",domain,username,password);
    if(fclose(file)!=0){
        errorFTCF();
    }

}

void recordRead(void){
    FILE* file;
    char data[3][100];
    char line[300];
    char* ptr;

    file = fopen("data.txt","r");
    if(file==NULL){
        errorFTOF();
        return;
    }
    fseek(file,0,SEEK_SET);

    while(!feof(file)){
        ptr = fgets(line,100,file);
        if(ptr!=NULL){
            strcpy(data[0],strtok(line," "));
            strcpy(data[1],strtok(NULL," "));
            strcpy(data[2],strtok(NULL,"\n"));
            // data[2][strlen(data[2])-1]='\0';
            decryption(data[2]);
            //these widgets will create from scratch for every row (so I couldn't declare them globally)
            GtkWidget *row = gtk_list_box_row_new(); //main row box
            GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,2); //container for row elements
            GtkWidget *domain = gtk_entry_new(); //entry box for domain
            GtkWidget *username = gtk_entry_new(); //entry box for username
            GtkWidget *password = gtk_entry_new(); //entry box for password
            gunichar DotforPasswords= 0x25CF; //this dot will be shown when password is hidden

            //some settings for row box
            gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(row),FALSE); //cannot be activated 
            gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(row),FALSE); //cannot be selected 
            
            //settings for password entry box
            gtk_entry_set_visibility(GTK_ENTRY(password),FALSE); //initially disabled the visibility 
            gtk_entry_set_invisible_char(GTK_ENTRY(password), DotforPasswords); //setting dot as invisible character
            gtk_entry_set_icon_from_icon_name(GTK_ENTRY(password), GTK_ENTRY_ICON_SECONDARY, "view-reveal-symbolic.symbolic"); //eye icon
            gtk_entry_set_icon_activatable(GTK_ENTRY(password),GTK_ENTRY_ICON_SECONDARY, TRUE); //eye icon can be clicked
            g_signal_connect(password,"icon-press",G_CALLBACK(ShowPassword),NULL); //call back function to show and hide password

            //making entry boxes non-editable
            gtk_editable_set_editable(GTK_EDITABLE(domain), FALSE);
            gtk_editable_set_editable(GTK_EDITABLE(username), FALSE);
            gtk_editable_set_editable(GTK_EDITABLE(password), FALSE);

            //displaying text through entry boxes 
            gtk_entry_set_text(GTK_ENTRY(domain), (data[0]));
            gtk_entry_set_text(GTK_ENTRY(username), (data[1]));
            gtk_entry_set_text(GTK_ENTRY(password), (data[2]));

            //adding entry boxes to the row container
            gtk_box_pack_start(GTK_BOX(container),domain,TRUE,TRUE,0);
            gtk_box_pack_start(GTK_BOX(container),username,TRUE,TRUE,0);
            gtk_box_pack_start(GTK_BOX(container),password,TRUE,TRUE,0);

            //adding container to row box and row box to the main list
            gtk_container_add(GTK_CONTAINER(row),container);
            gtk_container_add(GTK_CONTAINER(list),row);
            gtk_widget_show_all(row);
        }
    }

    if(fclose(file)!=0){
        errorFTCF();
    }
    file=NULL;
}

void recordUpdate(char* domain,char* username,char* password){
    FILE*file,* temp;
    int found=1;
    char search[3][100];
    char line[300];
    char* ptr;
    encryption(password);

    file = fopen("data.txt","r");
    temp = fopen("temp.txt","w");
    if(file==NULL || temp==NULL){
        errorFTOF();
        return;
    }
    fseek(file,0,SEEK_SET);

    while(!feof(file)){
        ptr = fgets(line,100,file);
        if(ptr!=NULL){
            strcpy(search[0],strtok(line," "));
            strcpy(search[1],strtok(NULL," "));
            strcpy(search[2],strtok(NULL,"\n"));
            if(strcmp(search[0],domain)==0 && strcmp(search[1],username)==0 && found==1){
                fprintf(temp,"%s %s %s\n",domain,username,password);
                found=2;
            }else{
                fprintf(temp,"%s %s %s\n",search[0],search[1],search[2]);
            }
        }

    }
    if(found==1){
        errorRNF();
    }
    if(fclose(file)!=0 || fclose(temp)!=0){
        errorFTCF();
    }
    file=NULL; temp=NULL;

    remove("data.txt");
    rename("temp.txt","data.txt");
}

void recordDelete(char* domain,char* username){
    FILE*file,* temp;
    int found=1;
    char search[3][100];
    char line[300];
    char* ptr;

    file = fopen("data.txt","r");
    temp = fopen("temp.txt","w");
    if(file==NULL || temp==NULL){
        errorFTOF();
        return;
    }
    fseek(file,0,SEEK_SET);

    while(!feof(file)){
        ptr = fgets(line,100,file);
        if(ptr!=NULL){
            strcpy(search[0],strtok(line," "));
            strcpy(search[1],strtok(NULL," "));
            strcpy(search[2],strtok(NULL,"\n"));
            if(strcmp(search[0],domain)==0 && strcmp(search[1],username)==0 && found==1){
                found=2;
                printf("\nHello\n");
                continue;
            }else{
                fprintf(temp,"%s %s %s\n",search[0],search[1],search[2]);
            }
        }

    }
    if(found==1){
        errorRNF();
    }
    if(fclose(file)!=0 || fclose(temp)!=0){
        errorFTCF();
    }
    file=NULL; temp=NULL;

    remove("data.txt");
    rename("temp.txt","data.txt");
}

char* recordSearch(const char* domain, const char* username){
    FILE*file;
    char search[3][100];
    char line[300];
    char* ptr;

    file = fopen("data.txt","r");
    if(file==NULL){
        errorFTOF();
        return NULL;
    }
    printf("\nFile opened");
    fseek(file,0,SEEK_SET);

    while(!feof(file)){
        ptr = fgets(line,100,file);
        if(ptr!=NULL){
            strcpy(search[0],strtok(line," "));
            strcpy(search[1],strtok(NULL," "));
            strcpy(search[2],strtok(NULL,"\n"));
            if(strcmp(search[0],domain)==0 && strcmp(search[1],username)==0){
                char* pnt;
                // search[2][strlen(search[2])-1]='\0';
                decryption(search[2]);
                pnt = (char*)malloc(strlen(search[2])*sizeof(char));
                strcpy(pnt,search[2]);
                if(fclose(file)!=0){
                    errorFTCF();
                }
                file=NULL;
                return pnt;
            }
        }
    }
    errorRNF();
    return NULL;
    if(fclose(file)!=0){
        errorFTCF();
    }
    file=NULL;
}

//some other functions
void ShowPassword(GtkWidget *password,gpointer data){
    gboolean visi;
    visi = gtk_entry_get_visibility(GTK_ENTRY(password));
    
    if(visi){
        gtk_entry_set_visibility(GTK_ENTRY(password),FALSE);
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(password),GTK_ENTRY_ICON_SECONDARY,"view-reveal-symbolic.symbolic");
    }else{
        gtk_entry_set_visibility(GTK_ENTRY(password),TRUE);
        gtk_entry_set_icon_from_icon_name(GTK_ENTRY(password),GTK_ENTRY_ICON_SECONDARY,"view-conceal-symbolic.symbolic");
    }
}

void SettingWindowSize(GtkNotebook *notebook,GtkWidget *page,guint page_num,gpointer user_data){
    if(page_num!=0){
        gtk_window_resize(GTK_WINDOW(ChamberOfSecrets),520,170);
    }else{
        gtk_window_resize(GTK_WINDOW(ChamberOfSecrets),520,520);
    }
}

gboolean PassWordHealth(GtkWidget* widget, GdkEventKey* event,gpointer user_data){
    GtkWidget* ptr = (GtkWidget*)widget;
    GtkWidget* hlt = (GtkWidget*)user_data;
    char* password = (char*)gtk_entry_get_text(GTK_ENTRY(ptr));


    if(event->type == GDK_KEY_PRESS){
        if(strcmp(password,"")!=0 && password!=NULL){
            int lowercase=0, uppercase=0, numbers=0, special=0;
            for (int i=0; i<strlen(password); i++){
                if ( *(password+i)>='A' && *(password+i)<='Z' )
                    uppercase=1;
                if ( *(password+i)>='a' && *(password+i)<='z' )
                    lowercase=1;
                if ( *(password+i)>='0' && *(password+i)<='9' )
                    numbers=1;
                if( *(password+i)>='#' && *(password+i)<='&' )
                    special=1;
            }
            int strength=lowercase+uppercase+numbers+special;
            switch (strength){
            case 4:
                gtk_entry_set_text(GTK_ENTRY(hlt),"* * * *");
                break;
            case 3:
            case 2:
                gtk_entry_set_text(GTK_ENTRY(hlt),"* * *");
                break;
            default:
                gtk_entry_set_text(GTK_ENTRY(hlt),"*");
                break;
            }
        }else{
            gtk_entry_set_text(GTK_ENTRY(hlt),"");
        }
    }
}


/*Encryption and Decryption*/
void encryption(char* key){
    for(int i=0;i<strlen(key);i++){
        if(isupper(key[i])!=0){
            key[i] = ((key[i]-'A'+5)%26)+'A';
        }else if(islower(key[i])!=0){
            key[i] = ((key[i]-'a'+5)%26)+'a';
        }else if(isdigit(key[i])!=0){
            key[i] = ((key[i]-'0'+5)%10)+'0';
        }
    }
}

void decryption(char* key){
    for(int i=0;i<strlen(key);i++){
        if(isupper(key[i])!=0){
            key[i] = ((key[i]-'A'+21)%26)+'A';
        }else if(islower(key[i])!=0){
            key[i] = ((key[i]-'a'+21)%26)+'a';
        }else if(isdigit(key[i])!=0){
            key[i] = ((key[i]-'0'+5)%10)+'0';
        }
    }
}

/*Verification System*/
bool verification(char* email, char* password){
    if(strcmp(email,"k230554@gmail.com")==0){
        if(strcmp(password,"123456789")==0){
            return true;
        }
    }
    return false;
}