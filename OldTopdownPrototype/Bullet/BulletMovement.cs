using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletMovement : MonoBehaviour
{
    private bool _isMotionSetted = false;
    private float _speed = 7f;
    private Vector3 direction;

    void Update()
    {
        if (_isMotionSetted)
        {
            transform.position += direction * Time.deltaTime * _speed;
        }
    }

    public void SetMotion(Vector3 dir)
    {
        direction = dir;
        _isMotionSetted = true;
    }

    public Vector3 GetDirection()
    {
        return direction;
    }
    
}
