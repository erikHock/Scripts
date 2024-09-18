using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GunFiring : MonoBehaviour
{
    [SerializeField] private Transform _gunBarrel;
    [SerializeField] private GameObject _bulletPrefab;
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            var spawnedBullet = Instantiate(_bulletPrefab, _gunBarrel.position, Quaternion.identity);
            spawnedBullet.GetComponent<BulletMovement>().SetMotion(transform.forward);
        }
    }
}
