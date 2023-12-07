using UnityEngine;
using System.Collections;
using UnityEditor;
using System.IO;


[CustomEditor(typeof(I2UParser))]
public class I2UEditor : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();

        I2UParser myScript = (I2UParser)target;
        if (GUILayout.Button("Load Scene"))
        {
            myScript.SpawnFromFile();
        }

        if (GUILayout.Button("Save Scene"))
        {
            myScript.SaveToFile();
        }

        if (GUILayout.Button("Remove All Spawned Objects"))
        {
            myScript.RemoveAllSpawnedObjects();
        }
        
    }
}

public class HandleTextFile
{
    [MenuItem("Tools/Write file")]
    static void WriteString()
    {
        string path = "Assets/test.level";
        //Write some text to the test.txt file
        StreamWriter writer = new StreamWriter(path, true);
        writer.WriteLine("Test");
        writer.Close();
        //Re-import the file to update the reference in the editor
        AssetDatabase.ImportAsset(path);
        TextAsset asset = (TextAsset)Resources.Load("test");
        //Print the text from the file
        Debug.Log(asset.text);
    }
    [MenuItem("Tools/Read file")]
    static void ReadString()
    {
        string path = "Assets/test.level";
        //Read the text from directly from the test.txt file
        StreamReader reader = new StreamReader(path);
        Debug.Log(reader.ReadToEnd());
        reader.Close();
    }
}