using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
using System.IO;

public class Spawner : MonoBehaviour
{
    [SerializeField] GameObject prefab;
    [SerializeField] float amount = 20.0f;

    public void SpawnObjects()
    {
        for (int i = 0; i < amount; i++)
        {
            float randX = Random.Range(-5, 5);
            float randY = Random.Range(5, 8);
            float randZ = Random.Range(-5, 5);

            Instantiate(prefab, new Vector3(randX,randY,randZ), Random.rotation);
        }
    }
}




