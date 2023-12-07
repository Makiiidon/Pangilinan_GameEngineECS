using System.Collections;
using UnityEngine;
using UnityEditor;
using System.IO;
using UnityEngine.SocialPlatforms;
using Unity.VisualScripting;
using System.Collections.Generic;


// Working I2UParser fetures:
// Can read files with .level format
// Can Save a .level file from game engine then reading file from Unity and vice-versa
// Spawns appropriate gameobjects read from the .level file

public class I2UParser : MonoBehaviour
{
    [SerializeField] GameObject plane;
    [SerializeField] GameObject cube;
    [SerializeField] string loadPath = "Assets/EngLevel.level";
    [SerializeField] string savePath = "Assets/saved.level";

    public void SpawnFromFile()
    {
        string file; // Overall File
        //Read the text from directly from the test.txt file
        StreamReader reader = new StreamReader(loadPath); // Get Data from Path
        file = reader.ReadToEnd(); // Place Data into (string)file
        reader.Close();

        string[] lines = file.Split('\n'); // Split by lines


        string objectName = "";
        string objectType = "";
        GameObject objectToSpawn = cube;
        Vector3 position = Vector3.zero;
        Quaternion rotation = Quaternion.identity;
        Vector3 scale = Vector3.one;
        string hasRigidbody = "0";
        float mass = 0;
        string hasGravityEnabled = "1";

        int index = 0;

        foreach (string line in lines)
        {
            if (index == 0) // Name
            {
                string[] stringSplit = line.Split('|');
                objectName = stringSplit[0];
			    index++;
            }
            else if(index == 1) // Type
            {
                string[] stringSplit = line.Split('|');
                objectType = stringSplit[1];
                if (stringSplit[1] == "1")
                {
                    objectToSpawn = cube;
                }
                

                hasRigidbody = stringSplit[3];
                if (stringSplit[1] == "4")
                {
                    hasRigidbody = "1";
                }
                mass = float.Parse(stringSplit[4]);
                hasGravityEnabled = stringSplit[5];
                index++;
            }
            else if (index == 2) // Position
            {
                string[] stringSplit = line.Split('|');
                position = new Vector3(float.Parse(stringSplit[1]), float.Parse(stringSplit[2]), float.Parse(stringSplit[3]));
                index++;
            }
            else if (index == 3) // Rotation
            {
                string[] stringSplit = line.Split('|');
                rotation = Quaternion.Euler(float.Parse(stringSplit[1]), float.Parse(stringSplit[2]), float.Parse(stringSplit[3]));
                index++;
            }
            else if (index == 4) // Scale
            {
                string[] stringSplit = line.Split('|');
                scale = new Vector3(float.Parse(stringSplit[1]), float.Parse(stringSplit[2]), float.Parse(stringSplit[3]));
                index = 0;

                GameObject spawnedObject = Instantiate(objectToSpawn, position, rotation);
                spawnedObject.transform.localScale = scale;
                spawnedObject.gameObject.name = objectName;
                spawnedObject.tag = "Spawned";

                if (hasRigidbody == "1")
                {
                    spawnedObject.AddComponent<Rigidbody>();
                    spawnedObject.GetComponent<Rigidbody>().mass = mass;
                    if (int.Parse(objectType) == 5)
                    {
                        spawnedObject.GetComponent<Rigidbody>().isKinematic = true;
                        spawnedObject.tag = "Kinematic";

                    }
                    if (hasGravityEnabled == "0")
                    {
                        spawnedObject.GetComponent<Rigidbody>().useGravity = false;
                    }
                    else if (hasGravityEnabled == "1")
                    {
                        spawnedObject.GetComponent<Rigidbody>().useGravity = true;
                    }
                    spawnedObject.AddComponent<BoxCollider>();
                }
            }

            //Debug.Log(line);
        }
    }

    public void SaveToFile()
    {
        //Write some text to the test.txt file
        StreamWriter writer = new StreamWriter(savePath, true);
        WriteOnFile(writer);
        writer.Close();
        //Re-import the file to update the reference in the editor
        AssetDatabase.ImportAsset(savePath);
        TextAsset asset = (TextAsset)Resources.Load("test");
        //Print the text from the file
        //Debug.Log(asset.text);
    }

    void WriteOnFile(StreamWriter writer)
    {
        List<GameObject> spawnedObjects = new List<GameObject>(GameObject.FindGameObjectsWithTag("Spawned"));
        foreach (GameObject kinematic in new List<GameObject>(GameObject.FindGameObjectsWithTag("Kinematic")))
        {
            spawnedObjects.Add(kinematic);
        }
        foreach (GameObject spawned in spawnedObjects)
        {
            string[] objName = spawned.name.Split(' ');
            string hasRigidbody = "0";
            string useGravity = "0";
            float mass = 0f;
            int objType = 2;
            if (objName[0] == "Cube" || objName[0] == "Cube_Physics" || spawned.name == "Cube\r")
                objType = 1;

            if (objName[0] == "Plane_Physics" || spawned.CompareTag("Kinematic") || spawned.name == "Plane_Physics\r")
                objType = 5;

            if (spawned.GetComponent<Rigidbody>())
            {
                hasRigidbody = "1";
                mass = spawned.GetComponent<Rigidbody>().mass;
                if (spawned.GetComponent<Rigidbody>().useGravity)
                {
                    useGravity = "1";
                }
            }

            Debug.Log(objName[0]);
            writer.WriteLine(spawned.name);
            writer.WriteLine("Type:|" + objType + "|none|" + hasRigidbody + "|" + mass + "|" + useGravity + "|");
            writer.WriteLine("Position:|" + spawned.transform.position.x + "|" + spawned.transform.position.y + "|" + spawned.transform.position.z + "|");
            writer.WriteLine("Rotation:|" + spawned.transform.eulerAngles.x + "|" + spawned.transform.eulerAngles.y + "|" + spawned.transform.eulerAngles.z + "|");
            writer.WriteLine("Scale:|" + spawned.transform.localScale.x + "|" + spawned.transform.localScale.y + "|" + spawned.transform.localScale.z + "|");
            
        }
    }

    public void RemoveAllSpawnedObjects()
    {
        GameObject[] spawned = GameObject.FindGameObjectsWithTag("Spawned");
        foreach (GameObject obj in spawned)
        {
            DestroyImmediate(obj);
        }

        GameObject[] spawnedKinematic = GameObject.FindGameObjectsWithTag("Kinematic");
        foreach (GameObject obj in spawnedKinematic)
        {
            DestroyImmediate(obj);
        }
    }
}


