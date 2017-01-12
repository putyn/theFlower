Attribute VB_Name = "add_nodes"
'double the numbers of nodes for a selected object
'select the object you want and run the macro
Public Sub add_nodes()
    Dim doc As Document
    Dim shape As shape
    
    Set doc = ActiveDocument
    Set shape = ActiveSelection.Shapes.First
    doc.Unit = doc.Rulers.HUnits
    
    'MsgBox "shape length " & shape.Curve.Length, vbOKOnly
    'MsgBox "curve segments " & shape.Curve.Segments.Count, vbOKOnly
    
    Dim segment_count As Integer
    segment_count_now = shape.Curve.Segments.Count
    Dim segment_count_end As Integer
        segment_count_end = segment_count_now * 2
        
    For segment_idx = 1 To segment_count_end - 1 Step 2
        shape.Curve.Segments(segment_idx).AddNodeAt (0.5)
    Next segment_idx
End Sub

