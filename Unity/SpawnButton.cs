using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;


[CustomEditor(typeof(Spawner))]
public class SpawnButton : Editor
{
    public override void OnInspectorGUI()
    {
        DrawDefaultInspector();

        Spawner myScript = (Spawner)target;
        if (GUILayout.Button("Spawn Objects"))
        {
            myScript.SpawnObjects();
        }
    }
}
