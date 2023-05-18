#include"ProHeader.h"
#include"MYFMath.h"
#include"MatixOperation.h"
static ProName msg_file;

ProError UsrActivateCurrentWindow()
{
    int window_id;
    ProError status;
    status = ProWindowCurrentGet(&window_id);
    status = ProWindowActivate(window_id);
    return status;
}

/*================================================================*\
  FUNCTION: UserSolidNoteCreate()
  PURPOSE:  Example of note creation for solids
\*================================================================*/
int UserSolidNoteCreate()
{
#define MAX_NOTE_LEN PRO_LINE_SIZE

    int             err;
    ProSelection* p_sel;                /* for selection */
    int             n_sel;
    ProModelitem    note_owner;           /* owner of the note */

    wchar_t** text_arr;             /* list of note text lines */
    ProMdl          model;                /* current model */
    ProLine         w_notetext;           /* line of note text */
    ProNote         note;                 /* note object */
    ProNoteAttach   note_attach;          /* attach information for
                         note */
    int             i;
    ProMouseButton  button;
    ProPoint3d      note_pos_scrn;        /* note position in screen
                         coordinates */
    ProPoint3d      outline[2];           /* points delimiting the
                         model outline */
    ProPoint3d      note_pos;             /* note position, in model
                         coordinates */
    ProMatrix       vmatrix, inv_vmatrix; /* view matrix and inverse */
    ProMatrix       def_matrix = { {1.0, 0.0, 0.0, 0.0},
                  {0.0, 1.0, 0.0, 0.0},
                  {0.0, 0.0, 1.0, 0.0},
                  {0.0, 0.0, 0.0, 1.0} };

    ProStringToWstring(msg_file, (char*)"msg_ugfund.txt");
    /*----------------------------------------------------------------*\
      Get the current model.
    \*----------------------------------------------------------------*/
    err = ProMdlCurrentGet(&model);
    if (err != PRO_TK_NO_ERROR)
    {
        ProMessageDisplay(msg_file, (char*)"USER %0s F",
            "Error getting current model.");
        return (err);
    }

    /*----------------------------------------------------------------*\
      Get the note text.
    \*----------------------------------------------------------------*/
    ProMessageDisplay(msg_file, (char*)"USER %0s F", "Enter note text.");
    err = ProMessageStringRead(MAX_NOTE_LEN, w_notetext);
    if (err != PRO_TK_NO_ERROR)
        return (err);
    /*----------------------------------------------------------------*\
      Fill the array of note lines.
    \*----------------------------------------------------------------*/
    err = ProArrayAlloc(1, sizeof(wchar_t*), 1, (ProArray*)&text_arr);
    text_arr[0] = &w_notetext[0];

    /*----------------------------------------------------------------*\
      Get the modelitem for the model.
    \*----------------------------------------------------------------*/
    err = ProMdlToModelitem(model, &note_owner);

    /*----------------------------------------------------------------*\
      Create the note to be owned by the model.
    \*----------------------------------------------------------------*/
    err = ProSolidNoteCreate(model, NULL, text_arr, &note);
   
    /*----------------------------------------------------------------*\
      Get the leaders and add to the attachment.
    \*----------------------------------------------------------------*/
    ProMessageDisplay(msg_file, (char*)"USER %0s F",
        "Select edges for leaders.");
    err = ProSelect((char*)"edge", -1, NULL, NULL, NULL, NULL, &p_sel,
        &n_sel);
    if (err != PRO_TK_NO_ERROR)
        return (err);

    err = ProNoteAttachAlloc(&note_attach);

    for (i = 0; i < n_sel; i++)
    {
        err = ProNoteAttachAddend(note_attach, p_sel[i],
            PRO_NOTE_ATT_NONE);
    }
    /*----------------------------------------------------------------*\
      Get the note position, in screen coordinates.
    \*----------------------------------------------------------------*/
    ProMessageDisplay(msg_file, (char*)"USER %0s F", "Select note location.");
    err = ProMousePickGet(PRO_LEFT_BUTTON, &button, note_pos_scrn);
    if (err != PRO_TK_NO_ERROR)
        return (err);

    /*----------------------------------------------------------------*\
      Get the view matrix (the transformation from model coordinates
      to screen coordinates) and invert.
    \*----------------------------------------------------------------*/
    err = ProViewMatrixGet(model, NULL, vmatrix);
    err = MYFMatrix::MYFMatrixInvert(vmatrix, inv_vmatrix);

    /*------------------------------------------------------------------*\
      Transform the note position from screen coordinates to model
      coordinates.
    \*----------------------------------------------------------------*/
    MYFMatrix::MYFPointTrans(inv_vmatrix, note_pos_scrn, note_pos);
    err = ProSolidDispoutlineGet((ProSolid)model, def_matrix, outline);

    /*----------------------------------------------------------------*\
      Set the note position in terms of model size parameters
      (see ProNote.h)
    \*----------------------------------------------------------------*/

    for (i = 0; i < 3; i++)
    {
        note_pos[i] = (note_pos[i] - outline[0][i]) /
            (outline[1][i] - outline[0][i]);
    }
    err = ProNoteAttachFreeSet(note_attach, note_pos[0], note_pos[1],
        note_pos[2]);
    err = ProNotePlacementSet(&note, note_attach);

    /*----------------------------------------------------------------*\
      Display the note.
    \*----------------------------------------------------------------*/
    err = ProAnnotationShow((ProAnnotation*)&note, NULL, NULL);
    /*----------------------------------------------------------------*\
      Free the memory.
    \*----------------------------------------------------------------*/
    err = ProNoteAttachRelease(&note_attach);
    err = ProArrayFree((ProArray*)&text_arr);
    UsrActivateCurrentWindow();
    return (PRO_TK_NO_ERROR);
}
