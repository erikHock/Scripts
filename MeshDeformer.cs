using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MeshDeformer : MonoBehaviour
{
    [Range(1f, 5f)]
    [SerializeField] private float _radius = 2f;

    [Range(1f, 5f)]
    [SerializeField] private float _deformationStrength = 2f;

    [Range(1f, 5f)]
    [SerializeField] private float _smoothingFactor = 2f;

    private Mesh _mesh;
    private Vector3[] _vertices, _modifiedVerts;
    private Camera _mainCam;

    private void Start()
    {
        _mainCam = Camera.main;
        _mesh = GetComponent<MeshFilter>().mesh;
        _vertices = _mesh.vertices;
        _modifiedVerts = _mesh.vertices;
    }

    private void RecalculateMesh()
    {
        _mesh.vertices = _modifiedVerts;
        GetComponent<MeshCollider>().sharedMesh = _mesh;
        _mesh.RecalculateNormals();
    }

    private void Update()
    {
        Ray ray = _mainCam.ScreenPointToRay(Input.mousePosition);

        if(Physics.Raycast(ray, out RaycastHit hit, Mathf.Infinity))
        {
            for (int v = 0; v < _modifiedVerts.Length; v++)
            {
                Vector3 distance = _modifiedVerts[v] - hit.point;
                
                float force = _deformationStrength / (1f + hit.point.sqrMagnitude);

                if(distance.sqrMagnitude < _radius)
                {
                    if (Input.GetMouseButton(0))
                    {
                        _modifiedVerts[v] = _modifiedVerts[v] + (Vector3.up * force) / _smoothingFactor;
                    } 
                    else if (Input.GetMouseButton(1))
                    {
                        _modifiedVerts[v] = _modifiedVerts[v] + (Vector3.down * force) / _smoothingFactor;
                    }
                }
            }
        }
     

        RecalculateMesh();
    }
}

