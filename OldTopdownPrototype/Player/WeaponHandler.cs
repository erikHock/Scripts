using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeaponHandler : MonoBehaviour
{
    private Plane _plane = new Plane(Vector3.up, 0);
    private Camera _cam;

    private float lastClampedAngle;

    [SerializeField] Transform _playerTransform;
    [SerializeField] Transform _gunHolder;


    private void Awake()
    {
        _cam = Camera.main;
    }
    void Update()
    {
        float distance;
        Ray ray = _cam.ScreenPointToRay(Input.mousePosition);

        if (_plane.Raycast(ray, out distance))
        {
            Vector3 targetPosition = ray.GetPoint(distance);
            
            Vector3 targetDirection = (targetPosition - _playerTransform.position).normalized;
            targetDirection.y = 0f; 

            // Calculate the angle between the player's forward direction and the target direction
            float angle = Vector3.SignedAngle(_playerTransform.forward, targetDirection, Vector3.up);
            float maxRotation = 45f;

            angle = Mathf.Clamp(angle, -40, 140);

            // Calculate the new rotation of the gun object
            Quaternion rotation = Quaternion.Euler(0f, angle, 0f);

            // If the player is not facing forward, use the last clamped rotation for the gun
            if (Mathf.Abs(angle) > 5f)
            {
                rotation = Quaternion.Euler(0f, lastClampedAngle, 0f);
            }
            
            // Set the rotation of the gun object around the player
            _gunHolder.rotation = _playerTransform.rotation * rotation;

            lastClampedAngle = angle;
            
        }

    }

}
